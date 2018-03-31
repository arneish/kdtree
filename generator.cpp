#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;
int main(){
    ofstream file;
    file.open("dim2data100.txt");
    file <<"2 100\n";
    for (int i=0; i<100; i++){
        double k = (rand()%10000)/10000.0;
        double j = (rand()%10000)/10000.0;
        file<<k<<" "<<j<<"\n";
    }
    file.close();
 return 0;
}