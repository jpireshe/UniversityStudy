#!/bin/bash

NUM_PREY=0
NUM_PRED=0

usage(){
cat 1>&2 <<EOF
Usage: $(basename $0) -y <PREY> -r <PREDATOR>

PREY is a single prey animal.
PREDATOR is a single predator animal.

If -s is not specified, search the entire file regardless of country or location.  If -s is not specified first, the behavior is undefined.

Note that -y and -r may be specified multiple times.  The number of each predator and prey should be added.

This script does not consider time.  It only counts total occurrences of an animal in the data file that occur within the specified state.

The search is case insensitive.

Ratio of hadrosaur animals to tyrannosaur:
    predatorprey.sh -y hadrosaur -r tyrannosaur

Ratio of stegasaur animals to allosaur:
    predatorprey.sh -y stegasaur -r allosaur
    
Ratio of hadrosaur and ceratop animals to tyrannosaur:
    predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur

Ratio of hadrosaur and ceratop animals to tyrannosaur, raptor, and allosaur:
    predatorprey.sh -y hadrosaur -y ceratop -r tyrannosaur -r raptor -r allosaur

EOF
exit $1
}

lookforprey() {
    local PREY=$1
    PREYLIST=$(cat dinosaur.dat | awk -v FS=$'\t' "{print \$6}" | sed -nE "/.*$PREY.*/Ip")
    while IFS='\n' read -a LINE; do
        NUM_PREY=$(echo "$NUM_PREY + 1" | bc -l)
    done <<< "$PREYLIST"
}

lookforpredator() {
    # sorry! no time to change to pred
    local PRED=$1
    PREDLIST=$(cat dinosaur.dat | awk -v FS=$'\t' "{print \$6}" | sed -nE "/.*$PRED.*/Ip")
    while IFS='\n' read -a LINE; do
        NUM_PRED=$(echo "$NUM_PRED + 1" | bc -l)
    done <<< "$PREDLIST"
}

# HINT: awk will ignore case if you add the variable IGNORECASE=1, like so:
# awk -v IGNORECASE=1 ***now the rest of your awk command***

while [ $# -gt 0 ]; do
    case $1 in
        -y) lookforprey $2; shift;;
        -r) lookforpredator $2; shift;;
    esac
    shift
done

# do not change these echo statements, I use them for grading
echo "number of prey: $NUM_PREY"
echo "number of predator: $NUM_PRED"

# just to be clear, you are calculating number of PREY divided by number of PREDATORS
# (I realize the script is called predatorprey, not preypredator.  Sorry.)

YRRAT=$(echo "$NUM_PREY/$NUM_PRED" | bc -l)

echo "ratio: $YRRAT"

