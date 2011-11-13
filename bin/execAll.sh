#!/bin/bash

for (( i = 0 ; i < 1000 ; i += 4 ))
do
    ./bin/bst data/$i-1000.in 
    ./bin/bst data/`expr $i + 1`-1000.in &
    ./bin/bst data/`expr $i + 2`-1000.in &
    ./bin/bst data/`expr $i + 3`-1000.in &
done
