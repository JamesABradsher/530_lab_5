#!/bin/sh

make clean
make

#Random Writes
echo "Running Random Writes"
echo "Running Random Writes" >> Output_R

block=4

while [ $block -le 131072 ]
do
    echo "Block: $block kb"
    echo "Block: $block kb" >> Output_R
    for i in 1 2 3 4 5 6 7 8 9 10
    do 
        ./utils -b $block\k -o Random.txt -x >> Output_R
    done
    block=`expr $block \* 2`
done

#Random Reads
echo "Running Random Reads"
echo "Running Random Reads" >> Output_R

block=4

while [ $block -le 131072 ]
do
    echo "Block: $block kb"
    echo "Block: $block kb" >> Output_R
    for i in 1 2 3 4 5 6 7 8 9 10
    do 
        ./utils -r -b $block\k -o Random.txt -x >> Output_R
    done
    block=`expr $block \* 2`
done

make clean