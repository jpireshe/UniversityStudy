''' Title: selection-sort-recursive.py
 * Abstract: 
    Write a program to rank cards and print out the names of the cardholders in the order of card ranking. (V)

    Create a dictionary called Hand that has the key : value pair as (name of the cardholder) : [rank, suit] (V)
    Your program must read the hand information from a file. (V)
        The first line in the file should have the number of hands - N. (V)
        The following lines must have <Name>, <Rank>, <Suit>. (V)

    N indicates the number of cardholders. (V)
    Name is the name of the cardholder. (V)
    Rank is the rank of the card: 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A. (ascending order) (V)
    Suit is the suit of the card: C, D, H, S (ie. clubs, diamonds, hearts, spades). S > H > D > C (V)

    You have to order the cardholders of each input set and display them such that the person with the  
    highest card value comes first, while the person with the lowest card value comes last. (V)

    You must order based on rank first and if there are ties break them using the suit of the card. (V)

    Your algorithm must be stable i.e., if there are two cardholders with the same rank and suit, their order must not change in your output. (V)

    Sample output: 
    Mary, Allison, Patrick, Chris (V)

 * Author: Joao Henares
 * Email: jpireshe@nd.edu
 * Estimate: 1h
 * Date: 10/23/2022
'''

#### class for data ####

# i wanted to use a struct but initializing it
# as a class seemed better
class cardData:
    def __init__(self, name, rank, suit):
        self.name = name
        self.rank = rank
        self.suit = suit

#### dict declarations ####
# to transform cards in 'numbers'
numericRanks = {'J': 11, 'Q': 12, 'K': 13, 'A': 14}

# to transform suits in 'numbers'
numericSuits = {'C': 1, 'D': 2, 'H': 3, 'S': 4}

# key: name of cardholder, value: [rank, suit]
hand = dict()

#### read file content ####
f = open(input("Name of file: "), "r")
l = 0
for line in f:
    line = line.rstrip()
    # get N #
    if l == 0:
        N = int(line)
    # get hand dict data #
    else:
        line = line.split(' ')
        hand[line[0]] = [line[1], numericSuits[line[2]]]
    l += 1

# transform rank into numbers (suit has already been transformed) #
for v in hand.values():
    if v[0] in ['J', 'K', 'Q', 'A']: v[0] = numericRanks[v[0]]
    else: v[0] = int(v[0])

# wrap data into one array of classes
arr = []
for k in hand.keys():
    arr.append(cardData(k, hand[k][0], hand[k][1]))

# insertion sort on arr
for i in range(len(arr)):
    j = i
    # double condition insertion sort (since this is not too big anyway)
    # so our condition is ((rank bigger) OR (rank equal AND suit bigger)) AND (j > 0)
    while ((arr[j].rank > arr[j-1].rank) or (arr[j].rank == arr[j-1].rank and arr[j].suit > arr[j-1].suit)) and (j > 0):
        t = arr[j]
        arr[j] = arr[j-1]
        arr[j-1] = t
        j -= 1


# print results as list 
i = 0
for k in arr:
    if i < len(arr) - 1:
        print(k.name, end=', ')
    else: 
        print(k.name, end='')
    i += 1
print(" ")