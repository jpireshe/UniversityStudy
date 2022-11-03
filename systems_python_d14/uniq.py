import sys

txt = open(sys.argv[1], "r")
dinodict = dict()

for line in txt:
    line = line.rstrip()
    dinodict[line] = line

for key in dinodict:
    print(dinodict[key])