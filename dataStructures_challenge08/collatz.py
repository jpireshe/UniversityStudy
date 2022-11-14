'''
Title:      table.py
Abstract:   Implement a Map class using a hash table with separate chaining.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   30 minutes
Date:       11/14/2022
Questions:
    1. What is stored in the table passed to cycle_length()?
        The key is the number, and the value is its cycle length computed from the function.

    2. How is table used in cycle_length() to implement memoization?
        Since the table gets the numbers and their cycle lengths, every time we try to compute them from now on
        the table can just look the value up, thus implementing memoization

    3. What number between 100 and 1000 (inclusive) has the longest cycle length?
        313 has 131 as its cycle length.
        
'''

from table import Map

import sys

# Functions

def cycle_length(n, table):
    ''' Return the collatz cycle length.
    >>> cycle_length(22, Map())
    16
    >>> cycle_length(58, Map())
    20
    >>> cycle_length(71, Map())
    103
    >>> cycle_length(1337, Map())
    45
    '''
    # base cases
    if n == 1: return 1

    # recursive call: not in cache
    if not table.lookup(n):
        if n % 2: table.insert(n, cycle_length(3*n + 1, table) + 1)
        else: table.insert(n, cycle_length(n//2, table) + 1)

    # recursive call: in cache
    return table.lookup(n)

# Main Execution

def main(stream=sys.stdin):
    ''' For each number in standard input, compute the cycle length, and print
    it out.
    >>> import io
    >>> main(io.StringIO('22\\n58\\n71\\n1337\\n'))
    Cycle Length of 22: 16
    Cycle Length of 58: 20
    Cycle Length of 71: 103
    Cycle Length of 1337: 45
    '''
    m = Map()

    for line in stream:
        line = line.rstrip()
        line = int(line)
        print("Cycle Length of " + str(line) + ": " + str(cycle_length(line,m)))


if __name__ == '__main__':
    main()
