#!/bin/bash

v=$(ls *.in)
f=$1

for e in $v
do
        echo $e
        $f < $e
done
