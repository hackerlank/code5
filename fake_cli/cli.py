
#!/usr/bin/python

import sys
import time

from netmsg.login_pb2 import *
from netmsg.move_pb2 import *

def packMsgBuffer(msg):
  buffer = msg.SerializeToString()
  l = 2 + len(buffer)
  packMsgId = msg._category << 12 | msg._msgId
  content =  chr(l) + chr(l>>8) + chr( packMsgId & 0xFF) + chr((packMsgId >> 8)& 0xFF) + buffer
  print "********************"
  print content
  return content

import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
print s.connect_ex(("127.0.0.1", 9913))

msg1 = LoginRequest()
msg1.username = "garfield"
msg1.passwd="cc3"

s.send(packMsgBuffer(msg1))

msg2 = MovePathRequest()
msg2.path.extend([1,2,3,4])

msg3 = MoveRequest()
msg3.x = 33
msg3.y = 88


while(True):
#	time.sleep(1)
	s.send(packMsgBuffer(msg2))
#	time.sleep(2)
	s.send(packMsgBuffer(msg3))


