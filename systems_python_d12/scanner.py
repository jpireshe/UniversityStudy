import socket

f = open("hosts.txt")

for line in f:
    host = line.split(":")[0]
    port = int(line.split(":")[1])

    try:
        s = socket.socket()
        s.settimeout(2)
        s.connect((host, port))

        dat = s.recv(64)
        dat = dat.decode('utf-8')
        dat = dat.rstrip()
    except socket.timeout as ex:
        dat = "<connection timeout>"
    

    s.close()

    print(f'{line.rstrip():28}  {dat}')

