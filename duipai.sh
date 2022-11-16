#!/bin/bash

gen=$1
std=$2
sol=$3

in="in"
out="out"
ans="ans"

for file in $gen $std $sol
do
    if ! test -x $file
    then
	echo "$file not an executable"
    fi
done

for (( i=1;i<100000;i++ ))
do
    echo "test #$i"
    $gen > $in
    $sol < $in > $out
    $std < $in > $ans
    if ! (diff -Z $out $ans)
    then
	echo "wrong answer"
	break
    fi
done
