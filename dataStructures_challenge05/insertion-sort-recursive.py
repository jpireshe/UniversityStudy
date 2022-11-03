''' Title: insertion-sort-recursive.py
 * Abstract: 
    Write a program (in Python) to implement the following sorting algorithms recursively:
    Insertion sort

    Your program should read input from the user and create a list of integers to sort.
 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 20m
 * Date: 10/23/2022
'''

# sort func
def sortInsertion(arr, i):
    # this is the base case. i basically created a recursive version of a for loop
    if i == len(arr): return
    # i also decided to do the while loop recursively given the nature of this assignment
    j = i
    swipeRecursive(arr, j)
    # now we call recursively for the next element!
    sortInsertion(arr, i+1)    
    
def swipeRecursive(arr, j):
    # base case: if we either have element already in a good place or j is out of range we break
    if (arr[j] >= arr[j-1]) or (j < 1): return
    # else, we swipe values and call recursively
    t = arr[j]
    arr[j] = arr[j-1]
    arr[j-1] = t
    swipeRecursive(arr, j-1)

# read in values from user
userOption = ' '
arr = []

while True:
    userOption = input("Please enter next integer. Input 'q' to quit: ")
    if userOption == 'q': break
    
    arr.append(int(userOption))

# print results

print("Your unsorted array is: " + str(arr))

sortInsertion(arr, 0)

print("Your sorted array is: ", str(arr))