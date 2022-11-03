''' Title: selection-sort-recursive.py
 * Abstract: 
    Write a program (in Python) to implement the following sorting algorithms recursively:
    Selection sort

    Your program should read input from the user and create a list of integers to sort.
 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/23/2022
'''

# sort func

def sortSelection(arr, i):
    # this is the base case. i basically created a recursive version of a for loop
    if i == len(arr): return

    # get min value and index
    min = arr[i]
    minindex = i

    def internalLoop(arr, j, min, mdex):
        #base case
        if j == len(arr): return min, mdex
        # check
        if arr[j] < min:
            min = arr[j]
            mdex = j
        # recursive call
        min, mdex = internalLoop(arr, j+1, min, mdex)
        return min, mdex
    
    # update min and minindex using func internalLoop()
    min, minindex = internalLoop(arr, i + 1, min, minindex)

    # swipe values in arr according to min and minindex
    tempval = arr[i]
    arr[i] = min
    arr[minindex] = tempval

    sortSelection(arr, i+1)


# read in values from user
userOption = ' '
arr = []

while True:
    userOption = input("Please enter next integer. Input 'q' to quit: ")
    if userOption == 'q': break
    
    arr.append(int(userOption))

# print results

print("Your unsorted array is: " + str(arr))

sortSelection(arr, 0)

print("Your sorted array is: ", str(arr))