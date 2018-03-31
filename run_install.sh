sudo apt-get install graphviz
g++ -std=c++11 kdtree.cpp construction.cpp -o arneish 
./arneish dim2data100.txt
python3 plot2d.py
