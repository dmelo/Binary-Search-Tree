#!/bin/bash
DATA='./data'

for (( i = 0; i < $1; i++ ))
do
    FILE="${DATA}/${i}-${1}.in"
    echo "generating file ${FILE}..."
    ./bin/randfile $2 > ${DATA}/${i}-${1}.in
done
