import socket
import sys

s = socket.socket()

s.bind(('student10', 8084))
# binds yourself to phone

s.listen() # phone rings, you answer it

# as soon as you pick up the phone, a new phone
# is created throgh which you answer what you
# listen in the first phone

while True:
    c, addr = s.accept() 
    # accepts call as soon as someone
    # sends something. c is the second phone
    # (other socket) and addr is something else

    while True:
        dat = c.recv(1024) 
        # receive message (up to 1 kb)
        if not dat:
            # no more message
            break

        dat = dat.decode('utf-8').rstrip()
        print(dat)

