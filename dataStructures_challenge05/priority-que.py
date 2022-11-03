''' Title: selection-sort-recursive.py
 * Abstract: 
    Write a program (in Python) to implement a priority queue. The PQ must have a front and back of the queue. 
    The priority queue must have the following functions:
    enque()
    deque()
    isEmpty()
    Display a menu with option: 1. Enque, 2. Deque, 3. Empty? 4. Display to the user to choose from.

 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/23/2022
'''

class priorityQueue:
    def __init__(self):
        self.list = []

    def enque(self, val):
        if self.isEmpty():
            self.list.append(val)
            return
        ### not empty: ###
        flag = 0 # checks for insertion  
        for i in range(len(self.list)):
            # this should sort the list by itself (imagine you are always putting at the position
            # of the biggest guy, you don't need to do some initial sort on the list.)
            if val > self.list[i]:
                self.list = self.list[:i] + [val] + self.list[i:]
                flag = 1
                break
            
        # smallest element case
        if flag == 0: self.list.append(val)
        

    def deque(self):
        if self.isEmpty(): return
        self.list.pop(0)

    def isEmpty(self):
        return not self.list

# the queue we will use 
theQueue = priorityQueue()

# user menu
while(True):
    useroption = int(input("1. Enque\n2. Deque\n3. Empty?\n4. Display\n5. Quit\nYour option: "))

    if useroption == 5: break

    elif useroption == 4: 
        print(str(theQueue.list))
        print(" ")

    elif useroption == 3:
        if theQueue.isEmpty(): print("The queue is empty.")
        else: print("The queue is not empty.")
        print(" ")

    elif useroption == 2:
        theQueue.deque()
        print(" ")

    elif useroption == 1:
        num = int(input("Please input number: "))
        theQueue.enque(num)
        print(" ")
    
