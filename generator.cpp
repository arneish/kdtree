#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;
int main(int argc, char** argv){
    ofstream file;
    file.open(argv[1]);
    int dim = atoi(argv[2]);
    int size = atoi(argv[3]);
    file <<dim<<" "<<size<<"\n";
    for (int i=0; i<size; i++){
	for (int j=0; j<dim; j++){
        double k = (rand()%(size*10))/(size*10.0);
        file<<k<<" ";
    }
	file<<"\n";
}
    file.close();
 return 0;
}
