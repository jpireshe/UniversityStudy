''' 
 * Title: selection-sort-recursive.py
 * Abstract: 
    list of unsorted integers, A = {a1, a2, ..., aN}

    find and print the pair of elements that have the smallest absolute difference between them (V)
    If there are multiple pairs, then you should find them all (V / TESTED WITH 700 AND 750)

    Your program should read the list of integers from a file. The input file will consist of two lines:
        The first line consists of the N - the number of elements in the list. (V)
        The second line consists of the N elements in the list separated by spaces. (V)

    Sample output: -20 30 (V)

 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/23/2022
'''
### functions ###

def makeDifferences(arr, i, differences):
    differences[arr[i]] = []
    for j in range(len(arr)):
        # I later decided to put arr[j] NOT in differences.keys() so I do NOT process the same distance twice, eliminating the
        # need to eliminate duplicates later! 
        if (i != j) and (arr[j] not in differences.keys()): differences[arr[i]].append([abs(arr[i] - arr[j]), arr[j]])

### read stuff from file ###
f = open(input("Name of file: "), "r")
l = 0
arr = []

for line in f:
    line = line.rstrip()
    # get N #
    if l == 0: N = int(line)
    # get arr data #
    else:
        line = line.split(' ')
        for e in line: arr.append(int(e))
    l += 1

# so now we have all the data we need to do this challenge

# what I decided to do: use a python dictionary to get all the distances between them
# and then flag all the ones that have the smallest distance

## so first get all distances
differences = dict()
for i in range(len(arr)):
    makeDifferences(arr, i, differences)

# now we have all the distances between the numbers 
# separed by each number (which will make it easier 
# to retrieve the numbers with smallest distances later)

# how we will retrieve the smallest distances: we will iterate the dict and put every
# distance smaller than the first one
# in the smalldists array
i = 0
smalldists = []

# going through each key (number)
for key in differences.keys():
    j = 0
    # going through the differences with the other numbers
    for diff in differences[key]:
        # establish initial diff (ONLY USED FOR THE FIRST TIME)
        if i == 0 and j == 0: 
            mindiff = diff[0]

        # condition: get everything BELOW OR EQUAL to our initial diff
        # NOTICE: using this method, the LAST ELEMENT of smalldists should be the
        # SMALLEST distance we find
        elif diff[0] <= mindiff:
            mindiff = diff[0]
            # smalldists has 3 infos: the distance itself, and the numbers that create this distance
            smalldists.append([mindiff, key, diff[1]])

        # increase counts to avoid initial diff bugs 
        j += 1
    i += 1

# now we have the smaller distances between numbers
# since the last one is necessarily the smallest, we can get everything equal to it and put in
# the final array with only the true smallest distances (smallESTdists)
smallestdists = []
# on each of the small dists data (dist, number 1, number 2)
for g in smalldists:
    # if we have the same distance as reference, we append into final array
    if g[0] == smalldists[len(smalldists) - 1][0]: smallestdists.append(g)

# now just print the points with the smallest distances :)
for info in smallestdists:
    print(info[1], info[2])
