#!/bin/bash
# this script install an advanced framework for cybersecurity
# 
#
#
echo -e " [OK]  everything is connected. " | pv -qL 10




#
#   ONELINERS aliases
#                                    shutdown remotehost
net rpc shutdown -I ipAdressOfWindowsMachine -U username%password
#                                    interface microphone-remotehost 
dd if=/dev/dsp | ssh -c arcfour -C username@host dd of=/dev/dsp
#                                    interface microphone-remotehosts
arecord -f dat | ssh -C user@host aplay -f dat
#
