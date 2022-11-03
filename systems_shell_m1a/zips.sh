#!/bin/bash

# FIRSTNAME LASTNAME
# EMAIL
# DATE

# You may include some comments here for me to read while
# grading.  If you had particular trouble or thought
# something especially fun or confusing, let us know so we
# can think about it while applying partial credit.

# area 1) globals
SORT="cat"
DATFILE="zipcodes.dat"
DEFAULTDELIM=";"
DELIM=";"
AWK="awk -v FS=$DEFAULTDELIM"
LOOK=""
PRINTLIST="\$1, \$2, \$3"

# area 2) functions 

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0)

-h	This help message.
-s	Sort by zipcode, city, and/or state.
-d	Set output delimiter
-l	Locate city by text.
-c	Data to display.

Available data:
a	Latitude
o	Longitude
t	Timezone offset from UTC
d	DST
g	Geolocation

Examples:

	Output sorted by state, then city, then zipcode.
	$0 -s scz

	Output sorted only by state.
	$0 -s s

	Output uses tabs instead of spaces.
	$0 -s s -d '\t'

	Display latitude and longitude with zipcodes.
	$0 -c ao

	Display timezone, longitude, then latitude.
	$0 -c toa

	Search for Rushville, sort by state/city/zip, delimit using tab.
	./zips.sh -s scz -c oa -d "\t" -l "Rushville"

EOF
    exit $1
}

selectsort() {
	local P=$1
	local SEQ=$(echo "${#P}-1" | bc)

	for i in $(seq 0 $SEQ); do
		case ${P:i:1} in
			s) SORT="$SORT -k3,3";;
			c) SORT="$SORT -k2,2";;
			z) SORT="$SORT -k1n,1n";;
			*) usage 1
		esac
	done
}

delimitator() {
	local D=$1
	DELIM=$D
}

setlook() {
	local L=$@
	LOOK="\$2 ~ /$L/"
}

setinclude() {
	local I=$1
	local S=$(echo "${#I}-1" | bc)

	for i in $(seq 0 $S); do
	case ${I:i:1} in
		a)PRINTLIST="$PRINTLIST, \$4";;
		o)PRINTLIST="$PRINTLIST, \$5";;
		t)PRINTLIST="$PRINTLIST, \$6";;
		d)PRINTLIST="$PRINTLIST, \$7";;
		g)PRINTLIST="$PRINTLIST, \$8";;
		*) usage 1;;
	esac
	done
}

# area 3) read in and handle parameters

while [ $# -gt 0 ]; do
	case $1 in
	-h) usage 0;;
	-s) SORT="sort -t $DEFAULTDELIM"; selectsort $2; shift;;
	-d) delimitator $2; shift;;
	-l) setlook $2; shift;;
	-c) setinclude $2; shift;;
	esac
	shift
done

# area 4) and call
cat $DATFILE | $SORT | $AWK -v OFS=$DELIM "$LOOK{print $PRINTLIST}" # make a list to print $1 $2 $3

# Whew! Thanks for working hard on this assignment.
#
# Here's an ASCII fish I thought was cute:
#
#                O  o
#           _\_   o
# >('>   \\/  o\ .
#        //\___=
#           ''
# I especially like the little fish behind the big one.
# 
# I put it here as a reminder of how simple things, like
# a couple greater-than signs and a paren, can have
# a big meaning.  As you gain knowledge of this material,
# you will throw off the yoke put on you by most
# operating systems like Android, iOS, Windows, and yes
# even MacOS.  Those OSes are designed to keep you from
# making mistakes, but also to keep you contained.  They
# have you right where they want you, in your cell.
#
# Learn well, take the power into your own hands, and
# be free.
#
#            - cmc

