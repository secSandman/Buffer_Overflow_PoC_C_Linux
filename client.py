#!/usr/bin/python

import socket
import struct
import sys

if len(sys.argv) != 2:
    print "Usage: " + sys.argv[0] + " [port]"
    sys.exit(1)

MESSAGE="A"

while len(MESSAGE) <= 1000000: #  may need to be increased based on your target buffer size 
	DEST_IP = '127.0.0.1' # host your vulnPrograms is listening on 
	DEST_PORT = int(sys.argv[1])
	counter=100
        MESSAGE += ("A" * counter) #increasing the fuzz payload of A's. 
	counter=counter+100 # 100 here is arbitrary, smaller will be more accurate but take longer.
        print("length of fuzz overflow is ")
	print(len(MESSAGE)) # For educational purposes 

	for string in MESSAGE:
		def convert(MESSAGE):
			raw = ''
			raw += struct.pack("<I", len(MESSAGE)) # Server expects a "pre-fix" telling you the buffer size
			raw += MESSAGE
			return raw
        # print(convert(MESSAGE))# test purposes 
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((DEST_IP, DEST_PORT))
	s.send(convert(MESSAGE))
	data = s.recv(1024)
s.close()

print "Received data: ", data
