#!/usr/bin/env python3

'''
Title:      cups.py
Abstract:   Determine the minimum amount of time require to fill all cups of water.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   1h
Date:       10/31/2022
Questiones:
    1. What is the worst-case time complexity of fill_cups()?
        O(n), would be n*log(n) if the number of elements (3) was not fixed.
    2. What is the worst-case space complexity of fill_cups()?
        O(1), as we have n = 3 fixed.
        Note for myself: Complexity has more to do with how it 
        GROWS over time rather than with how it starts.
    3. Why is this considered a greedy approach?
        because we are always trying to fill two cups, one of those always being
        that with most people waiting to get water.
'''

import sys
from priority_queue import PriorityQueue

# Functions

def fill_cups(cups):
    ''' Return minimum number of seconds required to fill all cups of water.
    Use a greedy algorithm by attempting to fill two types of cups at a time
    until there is only one remaining type.
    >>> fill_cups([1, 4, 2])
    4
    >>> fill_cups([5, 4, 4])
    7
    >>> fill_cups([5, 0, 0])
    5
    '''
    # queue cups by number of people waiting. do not use 0 cups.
    pq = PriorityQueue(cups)
    i = 0

    while(True):
        # pop queue, picking up what we will use 
        # (did this because it will always return the larger values)
        # null is what pop returns when no data.
        x1 = pq.pop()
        x2 = pq.pop()
        if x1 == 'null' and x2 == 'null': break

        # change seconds
        i += 1 
        # process if x1 and x2 make it back into the list
        if x1 != 'null': 
            x1 -= 1
            if x1 > 0: pq.push(x1)
        if x2 != 'null': 
            x2 -= 1
            if x2 > 0: pq.push(x2)


    return i

# Main Execution

def main(stream=sys.stdin):
    ''' For each line of cups, determine the minimum number of seconds required
    to fill all cups of water.
    >>> import io
    >>> main(io.StringIO('1 4 2\\n5 4 4\\n5 0 0\\n'))
    4
    7
    5
    '''
    for line in stream:
        line = line.rstrip("\n").split(" ")
        # make i a list (adapted to not use 0 cups)
        line = [int(line[i]) for i in range(len(line)) if line[i] != 0]
        r = fill_cups(line)
        print(r)

if __name__ == '__main__':
    main()