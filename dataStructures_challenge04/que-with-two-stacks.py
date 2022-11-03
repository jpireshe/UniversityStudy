''' Title: binary-converter.py
 * Abstract:
    create a queue with two stacks, using enque, deque and display
    to use enque, deque and display, you can use push, pop, top and isempty
 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/05/2022
'''

# queue functions

def enque(s1, val):
    s2 = stack()
    # throw s1 (reverse) into s2 to retrieve later
    while s1.isempty() == 0:
        s2.push(s1.top())
        s1.pop()

    # put value
    s1.push(val)

    # put s1 back (val goes to end)
    while s2.isempty() == 0:
        s1.push(s2.top())
        s2.pop()

    # this way, we have first in first out (queue)
    return s1

def deque(s1):
    if s1.isempty():
        return
    
    s1.pop()

def display(q):
    if q.isempty() == 0:
        print(q.list)
    else: print("The list is empty")

# stack class
class stack:
    def __init__(self):
        self.list = []

    def push(self, element):
        if self.list:
            self.list = [element] + self.list
        else:
            self.list = [element]

    def pop(self):
        if len(self.list) < 2:
            self.list = []
        else:
            self.list = self.list[1:]

    def top(self):
        if self.list:
            return self.list[0]

    def isempty(self):
        if not self.list:
            return 1
        else: return 0

#isEmpty: if ~(s)

# Initial queue: test case
theQueue = stack()
theQueue.push(5)
theQueue.push(7)
theQueue.push(1)
theQueue.push(1)
print("Initial queue:")
display(theQueue)

while True:
    print("0. Quit")
    print("1. Display queue")
    print("2. Enque")
    print("3. Deque")
    userchoice = input("Enter your option: ")

    if int(userchoice) == 0:
        break

    elif int(userchoice) == 1:
        display(theQueue)

    elif int(userchoice) == 2:
        val = int(input("Element to be enque'd: "))
        enque(theQueue, val)
        display(theQueue)
    
    elif int(userchoice) == 3:
        deque(theQueue)
        display(theQueue)

    else:
        print("Invalid.")
    
    print(" ")