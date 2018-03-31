#include <stdio.h>
#include<fstream>
#include<sstream>
#include<string>
#include<bits/stdc++.h>
#include <iostream>
#include "kdtree.h"
using namespace std;


int main(int argc, char **argv){
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
    cout<<"s: "<<s<<endl;
    double d;
    while(iss >> d){
        v.push_back(d);
    }
    data.push_back(v);
    masterlist.push_back(counter++);
}

for (int i=0; i<size; i++)
    {for (int j=0; j<dim; j++)
        cout<<data[i][j]<<" ";
        cout<<endl;    
    }

Node *root = kdconstruct(masterlist, data, 0, dim);
cout<<endl;
cout<<"root: median "<<root->lchd->median<<" :"<<root->lchd->list.size();

vector<graphvizNode*> gv;
int start=0;
traverse(root, data, gv, start);
cout<<endl<<"gv size:"<<gv.size();


ofstream file, edge;
file.open("plotdata.txt");
edge.open("plotedges.txt");
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