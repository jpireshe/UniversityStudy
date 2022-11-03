# unique.py
# check README.md to see usage
# joao henares, CSE 20289.01

import sys

# PROCESS COMMAND LINE ARGUMENTS

# a little help i made for when people use the program wrongly
helpdoc = "See README.md for instructions!"

# parameters to indicate what the user has input
numOccurences = 0
onlyDuplicates = 0
lowerCase = 0
onlyUnique = 0

# get from -c -d -i -u what to activate
for arg in sys.argv[1:]:
    if arg == '-c':
        numOccurences = 1
    elif arg == '-d':
        if onlyUnique == 0:
            onlyDuplicates = 1
        else: 
            print(helpdoc) # printing help if you either put -something out
            quit()         # of the manual or if you put only duplicates AND
                           # only uniques
    elif arg == '-i':
        lowerCase = 1
    elif arg == '-u':
        if onlyDuplicates == 0:
            onlyUnique = 1
        else: 
            print(helpdoc)
            quit()
    else:
        print(helpdoc)
        quit()

# PROCESS cat content

# put everything into a dict.
# notice that -i has already been done after this step
contents = dict()
for a in sys.stdin:
    line = a.rstrip()
    if lowerCase == 1: line = line.lower() # just make the line its lowercase version
    if line not in contents.keys(): # put everything starting with 1 in dict (if not already there)
        contents[line] = 1
    else:                           # if already in dict, increment by 1
        contents[line] += 1

# now iterate dict
for key in contents.keys():
    # stablish printline as either only the word or count + word (-c done)
    printline = key
    if numOccurences == 1:
        printline = str(contents[key]) + " " + printline
    
    # stablish what to print based on only duplicates, only uniques or other cases
    # (-d -u done)
    if onlyDuplicates == 1:
        if contents[key] > 1:
            print(printline)
    elif onlyUnique == 1:
        if contents[key] == 1:
            print(printline)
    else:
        print(printline)