#!/bin/bash
DATA='./data'

for (( i = 0; i < 100; i++ ))
do
    FILE="${DATA}/${i}-${1}.in"
    echo "generating file ${FILE}..."
    ./randfile $1 > ${DATA}/${i}-${1}.in
done
