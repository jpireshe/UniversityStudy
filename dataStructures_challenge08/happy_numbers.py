'''
Title:      table.py
Abstract:   Implement a Map class using a hash table with separate chaining.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   30 minutes
Date:       11/14/2022
Questions:
    1. How is seen used in is_happy()?
        Seen tracks if we get into any number we've been to, thus entering a loop. If we get
        in a seen number, we know it is not happy.

    2. How is table used in is_happy() to implement memoization?
        Table stores reults of is_happy(). So, eventually, if we got to any happy number
        we could just finish the process.

    3. How many happy numbers are there between 1 and 100 (inclusive)?
        23
'''

from table import Map
import sys

# Functions

def is_happy(n, seen, table):
    ''' Return whether or not n is a happy number.
    >>> is_happy(19, Map(), Map())
    True
    >>> is_happy(2, Map(), Map())
    False
    >>> is_happy(68, Map(), Map())
    True
    >>> is_happy(75, Map(), Map())
    False
    >>> is_happy(91, Map(), Map())
    True
    '''
    # base case: verify if any digits are different from 1 or 0
    digits = map(int, str(n))
    flag = 0
    sum = 0
    for digit in digits: 
        if digit != 1 and digit != 0: flag = 1
        sum += digit ** 2
    if flag == 0: return True
    
    # base case: we run into a seen number
    if seen.lookup(n) != None: return False

    # if we did not run into a seen number, we insert it here
    seen.insert(n, 0)

    # recursive call memoized
    if table.lookup(n) == None: table.insert(n, is_happy(sum, seen, table))

    # return memoized
    return table.lookup(n)

# Main Execution

def main(stream=sys.stdin):
    ''' For each number in standard input, determine if it is a happy number,
    and print it out.
    >>> import io
    >>> main(io.StringIO('19\\n2\\n68\\n75\\n91\\n'))
    Is 19 Happy?: Yes
    Is 2 Happy?: No
    Is 68 Happy?: Yes
    Is 75 Happy?: No
    Is 91 Happy?: Yes
    '''
    seen = Map()
    table = Map()
    table.insert(12, False)

    for line in stream:
        line = int(line.rstrip())
        if is_happy(line, seen, table): print(f'Is {line} Happy?: Yes')
        else: print(f'Is {line} Happy?: No')
        seen = Map()

if __name__ == '__main__':
    main()