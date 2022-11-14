'''
Title:      treap.py
Abstract:   Implement a Map class using a treap.
Author:     John Pires Henares
Email:      jpireshe@nd.edu
Estimate:   2 hours and 30 minutes
Date:       11/07/2022
Questions:
    1. What is worst-case time complexity of Map.insert()?
        O(n)
    2. What is worst-case time complexity of Map.search()?
        O(n)
    3. What role does a Node's priority play during insertion?
        The Node's priority determines whether we have to rotate left and right in order to rearrange a tree
    4. How did you use a dictionary in Map._dump_tree() to help you print each
    level on a single line?
        I mapped each element to a level, and created a list of elements at a certain level
'''

from collections import deque, defaultdict
from dataclasses import dataclass
from random      import random
import pdb

# Classes

@dataclass
class Node:
    ''' Node with string key, int value, float priority, and left and right children. '''
    key: str
    value: int = 0
    priority: float = -1
    left: 'Node' = None
    right: 'Node' = None

class Map:
    ''' Map Implementation based on a treap. '''

    def __init__(self):
        ''' Initialize empty Map.
        >>> m = Map(); not m.root
        True
        '''
        self.root = None

    def insert(self, key, value, priority=None):
        ''' Insert key, value pair into Map.  If key is already in Map, then
        update value.
        >>> m = Map()
        >>> m.insert('D', 0, 60); m.root
        Node(key='D', value=0, priority=60, left=None, right=None)
        >>> m.insert('F', 1, 76); m.root.key        # Rotate Left
        'F'
        >>> m.insert('H', 2, 14); m.root.right.key
        'H'
        >>> m.insert('C', 3, 70); m.root.left.key   # Rotate Right
        'C'
        >>> m.insert('A', 4, 55); m.root.left.left.key
        'A'
        '''
        self.root = self._insert(self.root, key, value, priority)

    def _insert(self, node, key, value, priority=None):
        ''' Recursively insert key, value pair into Map. '''
        # base case: no node
        if node is None: return Node(key, value, priority= priority or random())

        # base case: key already exists
        if key == node.key:
            node.value += 1
            return node

        # recursive call: BST invariant
        if key < node.key:
            node.left = self._insert(node.left, key, value, priority)

            # treap priority comparison (we only need to do that with the side we update)
            if node.left.priority > node.priority:
                node = self._rotate_right(node)

        else: 
            node.right = self._insert(node.right, key, value, priority)
            # treap priority comparison (we only need to do that with the side we update)
            if node.right.priority > node.priority:
                node = self._rotate_left(node)
        
        return node

    def lookup(self, key):
        ''' Lookup key in Map and return associated value (None if missing).
        >>> m = Map()
        >>> d = [('sbn', '574'), ('eau', '715'), ('sna', 714), ('nyc', 646)]
        >>> for k, v in d: m.insert(k, v)
        >>> all(m.lookup(k) == v for k, v in d)
        True
        >>> m.lookup('stl')
        '''
        return self._lookup(self.root, key)

    def _lookup(self, node, key):
        ''' Recursively lookup key in Map and return associated value (None if
        missing). '''
        # base case: empty node
        if node is None: return None
        
        # left
        l = self._lookup(node.left, key)
        if l: return l
        # self
        if node.key == key: return node.value
        # right
        r = self._lookup(node.right, key)
        if r: return r

        # final case
        return None

    @staticmethod
    def _dump_tree(root):
        ''' Output tree keys in BFS (level-by-level) order.
        - Print out one level per line (with nodes separated by spaces).
        - Do not print any lines with only invalid nodes.
        >>> tree = Node('A', left=Node('B'), right=Node('C'))
        >>> Map._dump_tree(tree)
        A
        B C
        >>> tree = Node('A', left=Node('B', left=Node('C'), right=Node('D')), right=Node('E'))
        >>> Map._dump_tree(tree)
        A
        B E
        C D 0 0
        >>> tree = Node('A', left=Node('B'), right=Node('C', left=Node('D'), right=Node('E')))
        >>> Map._dump_tree(tree)
        A
        B C
        0 0 D E
        '''
        
        # create queue and our dictionary
        queue = deque([[root, 0]])
        dictionary = defaultdict(list)

        while queue:
            # pop and get height and node
            node, height = queue.pop()

            # exception: node is none
            if not node: 
                dictionary[height].append('0')
                continue
            
            # put in dictionary
            dictionary[height].append(node.key)

            queue.append([node.right,height + 1])
            queue.append([node.left, height + 1])

        # dictionary: [height, [values]]
        # so i is [values]
        for i in dictionary.values():
            # check for all zeroes and print
            flag = 0
            for k in i:
                if k != '0': flag = 1
            if flag == 1: print(" ".join(i))

    @staticmethod
    def _rotate_right(p):
        ''' Rotate the sub-tree at parent node to the right.
            P               CL
           / \             /  \
          CL CR     =>    GL   P
         /  \                 / \
        GL  GR              GR   CR
        >>> tree = Node('A', left=Node('B'), right=Node('C'))
        >>> Map._dump_tree(Map._rotate_right(tree))
        B
        0 A
        0 C
        >>> tree = Node('A', left=Node('B', left=Node('C'), right=Node('D')), right=Node('E'))
        >>> Map._dump_tree(Map._rotate_right(tree))
        B
        C A
        0 0 D E
        '''
        cl = p.left     # child left
        gr = cl.right   # grandchild right
        cl.right = p    # put p under cl
        p.left = gr     # put gr under p (bst rules)

        return cl

    @staticmethod
    def _rotate_left(p):
        ''' Rotate the sub-tree at parent node to the left.
            P               CR
           / \             /  \
          CL CR     =>    P   GR
            /  \         / \
           GL  GR       CL  GL
        >>> tree = Node('A', left=Node('B'), right=Node('C'))
        >>> Map._dump_tree(Map._rotate_left(tree))
        C
        A 0
        B 0
        >>> tree = Node('A', left=Node('B'), right=Node('C', left=Node('D'), right=Node('E')))
        >>> Map._dump_tree(Map._rotate_left(tree))
        C
        A E
        B D 0 0
        '''
        cr = p.right
        gl = cr.left
        cr.left = p
        p.right = gl

        return cr



