import argparse
import sys
import socket
import dinodata
import threading

def handle_call(c,addr):
    while True: 
        dat = c.recv(1024)
        dat = dat.decode('utf-8').rstrip()

        if not dat:                         # IF YOU RECEIVE A MESSAGE YOU DO NOT BREAK
            # no more message
            break

        # processing and getting ratio      # IF YOU DO NOT BREAK, YOU PROCESS THE DATA :)
        preys = dat.split('|')[0].split(',')
        preds = dat.split('|')[1].split(',')

        num_prey, num_pred, ratio = dinos.preypredrat(preys, preds)

        # send back                         # AND HERE YOU SEND IT BACK
        ret = f'{num_prey}\t{num_pred}\t{ratio}'
        ret = ret.encode('utf-8')
        c.send(ret)

# get port
parser = argparse.ArgumentParser()
parser.add_argument('-p', dest='port', type=int, default=9999, help='port number for connection')
args = parser.parse_args()

# listen on specified port
s = socket.socket()
s.bind(('localhost', args.port))
s.listen()                                  # THIS PUTS S INTO LISTEN MODE

# data from dinodata
dinos = dinodata.dinodata("")
dinos.readdinos("dinosaur.dat")

while True:                                 # THE PROGRAM STAYS RUNNING (THIS IS WHAT A SERVER DOES!)
    # data from server
    c, addr = s.accept()                    # YOU WAIT FOR A MESSAGE
    print("got connection from " + str(addr))

    ##### NEW PART: THREADING #######

    th = threading.Thread(target=handle_call, args=(c,addr))
        # shows the threader what it needs to execute
        # and what it needs to do so (args)

    th.start()    
    #################################

    # THE FOLLOWING LINE IS REPLACED: handle_call(c,addr)
    


