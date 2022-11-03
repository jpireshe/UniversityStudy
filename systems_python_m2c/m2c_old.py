import exrex
import argparse
import hashlib
import ray

# FUNCTIONS

@ray.remote
def encryptAndCompare(r, enclines, original):
    r = hashlib.md5(r.encode('utf-8'))
    r = r.hexdigest()

    for encline in enclines:
        if r == encline:
            s = "Found match: " + str(original) + " -> " + str(encline)
            return s
        else:
            s = ""
    return s

def encrlocal(regexList):
    e = []
    for r in regexList:
        r = hashlib.md5(r.encode('utf-8'))
        e.append(r.hexdigest())
    return e

# initiate ray here
#ray.init(log_to_driver=False)

# PROCESS COMMAND LINE ARGUMENTS

# a little help i made for when people use the program wrongly
helpDoc = "See README.md for instructions!"

# get -r, -t, -f, -e and -p arguments
parser = argparse.ArgumentParser() # my option was using arparse
parser.add_argument('-r', dest='regex', type=str, required=True, help='REGEX')
parser.add_argument('-t', dest='nThreads', type=int, default=1, help='NUMTHREADS')
threadlimit = 12
# mutually exclusive group on the rest
group = parser.add_mutually_exclusive_group()
group.add_argument('-f', dest='PWF', type=str, help='PWF')
group.add_argument('-e', dest='EPW', type=str, help='EPW')
group.add_argument('-p', dest='PW', type=str, help='PW')
args = parser.parse_args()
# check for either one of the group
if not args.PWF and not args.EPW and not args.PW: 
    print(helpDoc)
    quit()
    
# to not pass thread limit:
if args.nThreads > threadlimit:
    print("Exceeded thread limit!")
    quit()
else:
    ray.init(log_to_driver=False)

# GET ALL REGEXES (completing -r)
regexList = list(exrex.generate(args.regex))

# had to add -t functionality: it changed a lot this part!
# if args.nThreads > 1:
# i decided just to always turn ray on. so i commented the line above this one

# if we use more than 1 thread, we group our functions (as shown in oct 7 class)
# this was kinda hard however, as I had to go from n cores to n cores in a while loop.
# also, i did not figure out how to use multicore functionality besides doing the results = []
# line.
# I later had to put -f -e and -p here too. mixing it all just made the code way faster but messirer
    
# This part completes -f -e and -p by changing function inputs
enclines = []
if args.PWF:
    # read file
    f = open(args.PWF, "r", encoding='utf-8')
    # PUT IN A LIST
    for line in f.readlines():
        line = line.rstrip()
        enclines.append(line)
elif args.EPW:
    enclines.append(args.EPW)
elif args.PW:
    enclines.append(encrlocal([args.PW])[0])

# j tracks the line of regexList we're in
j = 0
# flag checks if we found something
# nFound checks how many we found (for multiple searches)
flag = 0
nFound = 0
while j < len(regexList) and (flag ==0):
    #  FLAG FOR FOUND: IF WE FIND SOMETHING WE WILL BREAK AND FINISH PROGRAM

    # if we have nthread thing to process
    if j + args.nThreads < len(regexList):
        # encrypting stuff and comparing results
        encresults = [encryptAndCompare.remote(regexList[i + j], enclines, regexList[i+j]) for i in range(args.nThreads)]
        encrr = ray.get(encresults)
        # encrr is a list of "" if there is no match
        # if it is a match, one of its elements becomes "found match: ..."
        # so we iterate looking for this element
        for c in encrr:
            if c: 
                # we print and break if we reach the same number of founds
                print(c)
                nFound += 1
                if nFound == len(enclines): 
                    flag = 1
                    break

    # if we have less than nthread things to process
    else:
        # (SEE ABOVE WHILE LOOP FOR EXPLANATION)
        encresults = [encryptAndCompare.remote(regexList[i + j], enclines, regexList[i+j]) for i in range(len(regexList) - j)]
        encrr = ray.get(encresults)
        for c in encrr:
            if c:
                # we print and break if we reach the same number of founds
                print(c)
                nFound += 1
                if nFound == len(enclines): 
                    flag = 1
                    break
        
    j += args.nThreads