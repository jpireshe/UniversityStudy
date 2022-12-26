import os
import sys
import time
import signal

def sigusr1_handler(signum, frame):
    print('haha no!')

signal.signal(signal.SIGUSR1, sigusr1_handler)

while True:

    time.sleep(1)
    print('y')

