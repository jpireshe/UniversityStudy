'''
Title:      anagrams.py
Abstract:   Determine if two words are anagrams.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   30 minutes
Date:       11/07/2022
Questions:
    1. What is the worst-case time complexity for count_letters()?
        O(nlogn)
    2. What is the worst-case time complexity ofr is_anagram()?
        O(nlogn)
'''

from treap import Map

import sys

# Functions

def count_letters(word):
    ''' Counts the occurrences of each letter in word and stores it in a Map
    (case insensitive).
    >>> counts = count_letters('aBbCcC')
    >>> counts.lookup('a')
    1
    >>> counts.lookup('b')
    2
    >>> counts.lookup('c')
    3
    >>> counts.lookup('d')
    '''
    # lower words, insert them in map
    m = Map()
    for i in range(len(word)): m.insert(word[i].lower(), 1)

    return m

def is_anagram(word_a, word_b):
    ''' Returns whether or not two words are anagrams.
    >>> is_anagram('anna', 'naan')
    True
    >>> is_anagram('banana', 'aNaNaB')
    True
    >>> is_anagram('SiLeNt', 'listen')
    True
    >>> is_anagram('KeK', 'eek')
    False
    >>> is_anagram('Nope', 'Topen')
    False
    >>> is_anagram('taco', 'cat')
    False
    '''
    # map word a and b
    ca = count_letters(word_a)
    cb = count_letters(word_b)
    
    # we will iterate these words here so I used lower()
    word_a = word_a.lower()
    word_b = word_b.lower()
    
    # flag if we find differences between words
    flag = 0

    # go through each letter of word_A, check in word_B
    for i in range(len(word_a)):
        if ca.lookup(word_a[i]) != cb.lookup(word_a[i]): flag = 1

    # do same other way (added because nope and topen were shown as anagrams)
    for j in range(len(word_b)):
        if cb.lookup(word_b[j]) != ca.lookup(word_b[j]): flag = 1

    if flag == 0: return True
    else: return False
    

# Main Execution

def main(stream=sys.stdin):
    ''' For each pair of words on each line, determine if they are anagrams,
    and print out the result.
    >>> import io
    >>> main(io.StringIO('taco cat\\nanna naan\\nSiLeNt listen\\n'))
    taco and cat are not anagrams!
    anna and naan are anagrams!
    SiLeNt and listen are anagrams!
    '''
    for line in stream:
        line = line.rstrip().split()
        result = is_anagram(line[0], line[1])
        if result: print(line[0], "and", line[1], "are anagrams!")
        else: print(line[0], "and", line[1], "are not anagrams!")

if __name__ == '__main__':
    main()