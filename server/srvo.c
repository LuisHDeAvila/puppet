/*
* srvo.c
*/
#inlcude <signal.h>
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
  if ((s_tep= t_open ("/dev/sdtarlan", O_RDWR, NULL)) < 0)
  {
    t_error("S:open failed");
    exit (2);
  }
  
  
