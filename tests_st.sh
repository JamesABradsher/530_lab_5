#!/bin/sh

make clean
make

#Sequntial Writes with Stride
echo "Running Strided Writes"
echo "Running Strided Writes" >> Output_ST

stride=4

while [ $stride -le 131072 ]
do
    echo "Stride: $stride kb" 
    echo "Stride: $stride kb" >> Output_ST
    for i in 4 64 256 1024 16384 128000 
    do 
        echo "Block: $i kb"
        echo "Block: $i kb" >> Output_ST
        for j in 1 2 3 4 5 6 7 8 9 10
        do 
            ./utils -b $i\k -s $stride -o Strided.txt >> Output_ST
        done
    done
    stride=`expr $stride \* 2`
done

#Sequential Reads with Stride
echo "Running Strided Reads"
echo "Running Strided Reads" >> Output_ST

stride=4

while [ $stride -le 131072 ]
do
    echo "Stride: $stride kb" 
    echo "Stride: $stride kb" >> Output_ST
    for i in 4 64 256 1024 16384 128000 
    do 
        echo "Block: $i kb"
        echo "Block: $i kb" >> Output_ST
        for j in 1 2 3 4 5 6 7 8 9 10
        do 
            ./utils -r -b $i\k -s $stride -o Strided.txt >> Output_ST
        done
        rm -f *.txt
    done
    stride=`expr $stride \* 2`
done
