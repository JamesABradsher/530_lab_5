#!/bin/sh
echo "Making Project"
make clean
make

#Sequntial Writes, No Stride
echo "Running Sequential Writes"
echo "Running Sequential Writes" >> Output

block=4

while [ $block -le 131072 ]
do
    echo "Block: $block kb"
    echo "Block: $block kb" >> Output
    for i in 1 2 3 4 5 6 7 8 9 10
    do 
        ./utils -b $block\k -o Sequential.txt >> Output
    done
    block=`expr $block \* 2`
done

#Sequential Reads, No Stride
echo "Running Sequential Reads"
echo "Running Sequential Reads" >> Output

block=4

while [ $block -le 131072 ]
do
    echo "Block: $block kb"
    echo "Block: $block kb" >> Output
    for i in 1 2 3 4 5 6 7 8 9 10
    do 
        ./utils -r -b $block\k -o Sequential.txt >> Output
    done
    block=`expr $block \* 2`
done

