#include <stdio.h>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<bits/stdc++.h>
#include <iostream>
#include "kdtree.h"
using namespace std;


int main(int argc, char **argv){

clock_t start;
double duration;
start = clock();

int size;
int dim;
string s;
vector < vector <double> > data;
vector<int> masterlist;
ifstream inFile;
inFile.open(argv[1]);
if (!inFile)
{
    cout<<"failed to open:";
    cerr<<"Unable to open file";
    exit(1);
}
getline(inFile, s);
istringstream is (s);
is >> dim>> size;
cout<<"dim: "<<dim<<endl<<"size: "<<size<<endl;
int counter =0;
while (getline(inFile, s))
{
    vector <double> v;
    istringstream iss(s);
    //cout<<"s: "<<s<<endl;
    double d;
    while(iss >> d){
        v.push_back(d);
    }
    data.push_back(v);
    masterlist.push_back(counter++);
}

// for (int i=0; i<size; i++)
//     {for (int j=0; j<dim; j++)
//         cout<<data[i][j]<<" ";
//         cout<<endl;    
//     }
int tracker = 0;
Node *root = kdconstruct(masterlist, data, 0, dim, tracker);
cout<<endl;
cout<<"root: median "<<root->lchd->median<<" :"<<root->lchd->list.size();


duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
cout<<"duration (min): "<< duration/60.0 <<'\n';

vector<graphvizNode*> gv;
int starter=0;
traverse(root, data, gv, starter);
cout<<endl<<"gv size:"<<gv.size();


ofstream file, edge;
file.open(argv[1]+"plotdata.txt");
edge.open(argv[1]+"plotedges.txt");
for (auto&i: gv){
    file<<"'"<<i->ID<<"'"<<"; "<<"'"<<i->display<<"'; \n";
}
for (auto&i: gv){
    for(auto&j: i->adjlist){
       edge<<"'"<<i->ID<<"'"<<","<<"'"<<j<<"'\n";//", constraint='false'"<<"\n";
       //edge<<i->ID<<","<<j<<"\n";
    }
}

file.close();
edge.close();
return 0;
}