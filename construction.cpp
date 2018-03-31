#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include<assert.h>
#include "kdtree.h"
using namespace std;

//kd-tree construction algorithms

//comparator for size<25 sorting
typedef pair<double, int> mypair;


bool comparator(const mypair &l, const mypair &r)
{
    return l.first < r.first;
}


//find median along dimension dim: [using quicksearch]
int findmedian(vector<int> s, vector<vector<double>> const &data, int dim, int k)
{
    //NOTE: argument 'k' starts from 1 not 0: (find "kth" largest point)
    int cursize = s.size();
    if (cursize < 20)
    {
        vector<mypair> temp;
        for (auto&i: s)
        {
            temp.push_back(make_pair(data[i][dim],i));
        }
        sort(temp.begin(),temp.end(), comparator);
        return temp[k-1].second;
    }
    int median_index = (cursize + 1) / 2;
    //cout << "size of the vector is:"<<cursize<<"  ";
    int pivot_index = rand() % (cursize); // [0, cursize-1]
    //int pivot = *std::next(s.begin(), pivot_index);
    int pivot = s[pivot_index];
    vector<int> left;
    vector<int> right;
    for (auto &i : s)
    {
        if (data[i][dim] < data[pivot][dim])
            left.push_back(i);
        else if (i!=pivot)
            right.push_back(i);
    }
    assert(left.size()+right.size()+1==s.size());
    //cout<<endl<<"pivot: "<<data[pivot][dim]<<" k:"<<k<<" : ";
    // for (auto&i: left)
    //     cout<<data[i]<<",";
    // cout<<endl;
    // for (auto&i: right)
    //     cout<<data[i]<<",";
    // cout<<endl;
    if (left.size()==k-1)
        //return data[pivot][dim];
        return pivot;
    else if (left.size() > k-1)
        return findmedian(left, data, dim, k);
    else
        return findmedian(right, data, dim, k-(left.size()+1));
}

Node* kdconstruct(vector<int> &list, vector< vector <double> > const &data, int depth, int &dim, int &tracker)
{
    if (list.size()==0)
        return nullptr;

    cout<<++tracker<<endl;
    int axis = depth % dim; //choose axis (dimension) to be split along

    int pivot = findmedian (list, data, axis, (list.size()+1)/2); //splitting index at axis
    double median = data[pivot][axis];
    vector<double>minvec;
    vector<double>maxvec;
    for (int j=0; j<dim; j++)
    {
        double min=1, max=0;
        for (int i=0; i<data.size(); i++)
        {
            if (data[i][j]>max)
                max = data[i][j];
            if (data[i][j]<min)
                min = data[i][j];
        }
        minvec.push_back(min);
        maxvec.push_back(max);
    }
    Node *n = new Node(axis, list, pivot, median, minvec, maxvec);
    cout<<"axis:"<<axis<<endl;//<<", pivot:"<<pivot<<", median:"<<median<<endl;
    vector<int> leftindex;
    vector<int> rightindex;
    for (auto&i: list)
    {
        if (data[i][axis]<median)
            leftindex.push_back(i);
        else if (i!=pivot)
            rightindex.push_back(i);
    }
    //cout<<"leftindex size/rightindex size/list size:"<<leftindex.size()<<"/"<<rightindex.size()<<"/"<<list.size()<<endl;
    assert (leftindex.size()+rightindex.size()+1 == list.size());
    n->lchd = kdconstruct(leftindex, data, depth+1, dim, tracker);
    n->rchd = kdconstruct(rightindex, data, depth+1, dim, tracker);
    return n;
}

void traverse(Node* root, vector<vector<double>> const &data, vector<graphvizNode*> &v, int &counter){
    int curID = counter;
    ostringstream strs, strs2;
    double x = data[root->pivot][0];
    double y = data[root->pivot][1];
    strs<<x;
    strs2<<y;
    string s ="("+ strs.str()+"," +strs2.str()+")";
    //string s = "("+(char*)(&x)+","+(char*)(&y)+")";
    vector<int> adjlist;
    if (root->lchd!=nullptr){
        adjlist.push_back(counter+1);
        traverse(root->lchd, data, v, ++counter);
    }
    if (root->rchd!=nullptr){
        adjlist.push_back(counter+1);
        traverse(root->rchd, data, v, ++counter);
    }
    graphvizNode* gv = new graphvizNode(curID, s, adjlist);
    v.push_back(gv);
    return;
}
