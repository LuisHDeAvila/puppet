/*
* srvo.c
*/
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/tiuser.h>

int t_errno;

main (argc, argv)
int argc;char *argv[];
{
  FILE *exec_p;
  char dat_p[1024];
  char cmd_p[1024];
  int dat_n;
  int s_tep;
  int flags;
  
  struct t_bind *bindreq_p;
  struct t_call *callind_p;
  if ((s_tep= t_open("/dev/sdtarlan", O_RDWR, NULL)) < 0)
  {
    t_error("S:open failed");
    exit (2);
  }
  bindreq_p = (struct t_bind *) t_alloc(s_tep,T_BIND,T_ALL);
  bindreq_p->addr.maxlen = 16;
  bindreq_p->addr.len =strlen(argv[1]);
  strncpy(bindreq_p->addr.buf, argv[1], 16);
  bindreq_p->qlen = 1;
  if (!lname2addr(s_tep, &(bindreq_p->addr)))
  {
    t_error("S:Name conversion failed");
    exit(3);
  }
  if(t_bind(s_tep,bindreq_p,NULL) <0)
  {
    t_error("S:Bind failed");
    exit(4);
  }
  callind_p = (struct tcall *) t_alloc(s_tep, T_CALL, T_ALL);
  if (t_listen(s_tep, callind_p) < 0)
  {
    t_error("S:Listen failed\n");
    exit(5);
  }
  if (t_accept(s_tep, s_tep, callind_p) < 0)
  {
    t_error("S:Accept failed");
    exit(6);
  }
  if(t_rcv(s_tep, cmd_p, sizeof(cmd_p), &flags) < 0)
  {
    t_error("S:Cmd Receive failed");
    exit(2);
  }
  if (!(exec_p = poppen(cmd_p, "r")))
  {
    perror("S:File Open of %s failed\n", cmd_p);
    exit(3);
  }
  while ((dat_n = fread(dat_p, 1, sizeof(dat_p), exec_p)) > 0)
  {
    if (t_snd(s_tep, dat_p, dat_n, 0) <0)
    {
      t_error("S:Data send failed");
      exit(4);
    }
  }
  if(ferror(exec_p))
  {
    perror("S:File Read failed")
    exit(5);
  }
  sleep(2);
  if(t_snddis(s_tep, NULL) < 0)
  {
    t_error("S:Disconnect failed");
    exit(6);
  }
  pclose(exec_p);
  exit(0);
}
  
  
