'''
Title:      balanced.py
Abstract:   Determine wether or not a binary tree is balanced.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   30 minutes
Date:       11/07/2022
Questions:
    1. What is the worst-case time complexity of is_balanced()?
        O(n), as we need to check all nodes
    2. What information does is_balanced() return?
        1. Whether the tree is balanced and 2. its height.
'''

import sys
from dataclasses import dataclass
import pdb

# classes

@dataclass
class Node:
    value: int
    left: 'Node' = None
    right: 'Node' = None

# Functions

def is_balanced(array, index=0):
    ''' Determine whether or not a binary tree is balanced.
    A binary tree is balanced if:
    1. Left and right sub-trees are balanced.
    2. Difference between heights of left and right sub-trees is no more than 1.
    >>> is_balanced([5, 3, 6])
    (True, 2)
    >>> is_balanced([5, 3, 6, 4])
    (True, 3)
    >>> is_balanced([5, 3, 0, 4])
    (False, 3)
    >>> is_balanced([5, 3, 4, 0, 1])
    (True, 3)
    >>> is_balanced([5, 3, 4, 0, 1, 0, 0, 0, 0, 2])
    (False, 4)
    '''
    # base case: out of range
    if index >= len(array) or array[index] == 0: return True, 0
    
    # left and right heights and results
    left, lh = is_balanced(array, 2*index + 1)
    right, rh = is_balanced(array, 2*index + 2)

    return abs(lh - rh) <= 1 and left == True and right == True, max(lh, rh) + 1

# Main Execution

def main(stream=sys.stdin):
    ''' For each line with a tree given in BFS format, output whether or not it
    is balanced.
    >>> import io
    >>> main(io.StringIO('5 3 6\\n5 3 6 4\\n5 3 0 4\\n'))
    Balanced
    Balanced
    Not Balanced
    '''
    for line in stream:
        line = line.rstrip().split(" ")
        line = [int(i) for i in line]
        if(is_balanced(line)[0]): print("Balanced")
        else: print("Not Balanced")

if __name__ == '__main__':
    main()