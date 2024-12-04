#!/bin/sh
echo "Running Sequential Writes"

block=4

while [ $block -le 10 ]
do
    echo "$block kb"
    i=0
    for i in 1 2 3 4 5 
    do 
        ./utils -b $block\k
    done
    block=`expr $block \* 2`
done