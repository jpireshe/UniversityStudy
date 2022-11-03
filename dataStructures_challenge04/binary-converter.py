''' Title: binary-converter.py
 * Abstract:
    uses the Stack code (from Lab05 in Python) 
    and prompts the user to enter a positive 
    integer number, and uses a stack to convert 
    that number to binary. If the number is less 
    than 1, exit the program. 
 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/05/2022
'''

# functions
def push(n, st):
    return [n] + st

def convert(n):
    st = []
    while(n > 0):
        if n % 2 == 1: st = push(1, st)
        else: st = push(0, st)
        n = int(n/2)
    return st


# program loop
while(True):
    # reset stack
    theStack = []

    # get user input and check if it is less than 1
    userNum = int(input("Enter a number: "))
    if userNum < 1: break

    theStack = convert(userNum)

    print(userNum, " => ", end="")
    for i in theStack:
        print(i, end="")
    print(" ")

    
