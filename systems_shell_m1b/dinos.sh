#!/bin/bash

OFS=";"
SORT="cat"

DATFILE="dinosaur.dat"

DINOA=$1
DINOB=$2

# Do some initial filtering here with awk

ALIST=$(cat $DATFILE | awk -v FS=$'\t' '{print $6, $16, $17}' | sed -nE "/.*$DINOA.*/Ip" | awk '{print $(NF-1), $NF}' | sort -t ';' -k1n,1n -k2n,2n | uniq -c | awk -v OFS=';' '{print $(NF-2), $(NF-1), $NF}')
BLIST=$(cat $DATFILE | awk -v FS=$'\t' '{print $6, $16, $17}' | sed -nE "/.*$DINOB.*/Ip" | awk '{print $(NF-1), $NF}' | sort -t ';' -k1n,1n -k2n,2n | uniq -c | awk -v OFS=';' '{print $(NF-2), $(NF-1), $NF}')

overlap_ma(){
    local XA=$1
    local XB=$2
    local IA=$3
    local IB=$4

    if [ $(echo "$XA > $IB" | bc) -eq 1 ]
    then 
        if [ $(echo "$XB > $IA" | bc) -eq 1 ]
        then 
            YN=1
        else 
            YN=0
        fi
    else 
        YN=0
    fi
}

YES_COUNT=0
NO_COUNT=0

for i in $ALIST
do 
    NUM_A=$(echo "$i" | awk -v FS=';' '{print $1}')
    MAX_A=$(echo "$i" | awk -v FS=';' '{print $2}')
    MIN_A=$(echo "$i" | awk -v FS=';' '{print $3}')
        for j in $BLIST
        do
            NUM_B=$(echo "$j" | awk -v FS=';' '{print $1}')
            MAX_B=$(echo "$j" | awk -v FS=';' '{print $2}')
            MIN_B=$(echo "$j" | awk -v FS=';' '{print $3}')
            overlap_ma $MAX_A $MAX_B $MIN_A $MIN_B
            if [ $YN -eq 1 ]
            then YES_COUNT=$(echo "$YES_COUNT+$NUM_B+$NUM_A" | bc)
            else NO_COUNT=$(echo "$NO_COUNT+$NUM_B+$NUM_A" | bc)
            fi
        done
done

# Recall the pseudocode from README.md:
#
#For each *unique* Allosaurus occurrence:
#      NUM_ALLOSAUR = number of times this Allosaurus timespan occurs
#      For each *unique* Stegosaurus occurrence:
#          NUM_STEGOSAUR = number of times this Stego timespan occurs
#          YN = overlap_ma(dinoA_maxma, dinoA_minma, dinoB_maxma, dinoB_minma)
#          if YN equals 1
#              yes_count += NUM_ALLOSAUR + NUM_STEGOSAUR
#          else
#              no_count += NUM_ALLOSAUR + NUM_STEGOSAUR



# Use bc to calculate $OVERLAP

OVERLAP=$(echo "100*$YES_COUNT/($YES_COUNT+$NO_COUNT)" | bc -l | awk -v FS='.' '{print $1}')
echo "dinoverlap between $DINOA and $DINOB is $OVERLAP%"

# Here's your ASCII art for this assignment!
#                __
#               / _)
#      _.----._/ /
#     /         /
#  __/ (  | (  |
# /__.-'|_|--|_|
#
# Imagine entering a time machine and setting the dial
# for -100 million years.  The door opens and humid air
# enters the machine.  Palm trees sway and a sauropod
# turns its long neck slowly toward you.  In the
# distance, a volcano emits steam and smoke.  A raptor
# suddenly leaps and runs toward you!  You look at the
# fuel gauge: if you jump again, you can make it home,
# but never return to the land of the dinosaurs.  Out
# of the corner of your eye you glance the emergency
# blaster pack. Fully charged, but locked behind the
# safety glass.  You just might have time to grab it,
# if you run now, right now.
#
# Do you punch JUMP or RUN?
#

