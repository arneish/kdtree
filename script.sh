#!/bin/bash
#nameofgeneratorfile dim size 
echo "<input data filename> <dim> <size>"
g++ -std=c++11 -o genex -O3 generator.cpp
./genex $1 $2 $3
cat $1
g++ -std=c++11 -o tragedy2 -O3 kdtree.cpp construction.cpp 
./tragedy2 $1 
rm tragedy2
rm genex
#python3 plot2d.py
