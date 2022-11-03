#!/usr/bin/env python3

'''
Title:      duplicates.py
Abstract:   Determine whether or not a line of words contains any duplicates.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   5 minutes
Date:       10/31/2022
Questiones:
    1. What is the average time complexity of detect_duplicates()?
        Since we have to insert every time and we are iterating n elements (with non fixed n)
        O(n*log(n))
    2. What is the worst-case time complexity of detect_duplicates()?
        Worst case insetion: n, so n*n = n^2
        O(n^2)
    3. What is the worst-case space complexity of detect_duplicates()?
        O(n) (we are inserting n elements into the set for n elements in the line with non fixed n)
    4. How would you modify the program to make it case in-sensitive?
        use line = line.lower() when getting the line from stream, so every input becomes lower
'''

import sys

from set import Set

# Functions

def detect_duplicates(words):
    ''' Return whether or not the sequence of words contains a duplicate.
    >>> detect_duplicates('a b c'.split())
    False
    >>> detect_duplicates('a b a'.split())
    True
    >>> detect_duplicates('a b c b e f'.split())
    True
    '''
    s = Set()
    for i in words:
        try: s.insert(i)
        except ValueError: return True
    
    return False

# Main Execution

def main(stream=sys.stdin):
    ''' For each line of words, determine if there are any duplicates.
    >>> import io
    >>> main(io.StringIO('a b c\\na b a\\na b c b e f\\n'))
    False
    True
    True
    '''
    for line in stream:
        line = line.lower().rstrip("\n").split(" ")
        print(detect_duplicates(line))

if __name__ == '__main__':
    main()