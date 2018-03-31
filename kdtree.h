#include <iostream>
#include <stdio.h>
#include <set>
using namespace std;

class Node
{
    //int ID;
  public:
    int split_dim;    //which dimension does this node split on
    int pivot;        //arg {data[i]} which is stoed in the node
    double median;    //data[i][split_dim]: value of the dimension at which split happens
    vector<int> list; //store the indices i of data[i] which is the input to the node
    Node *lchd;
    Node *rchd;
    vector<double> min;
    vector<double> max;

  public:
    Node(int split_dim, vector<int> &list, int pivot, double median, vector<double> const &min, vector<double>const &max)
    {
        //this->ID = ID;
        this->split_dim = split_dim;
        this->list = list;
        this->pivot = pivot;
        this->median = median;
        this->max = max;
        this->min = min;
    }
    bool isLeaf()
    {
        if (this->lchd == nullptr && this->rchd == nullptr)
            return true;
        else
            return false;
    }
};

int findmedian(vector<int>, vector<vector<double>> const &, int, int);

Node *kdconstruct(vector<int> &, vector<vector<double>> const &, int, int &, int &);

//graphvizNode only for plot purposes
class graphvizNode
{
  public:
    int ID;
    string display;
    double x;
    double y;
    vector<int> adjlist;
    vector <double> min; //size = dimension
    vector <double> max;
  public:
    graphvizNode(int ID, string display, vector<int> adjlist)
    {
        this->ID = ID;
        this->display = display;
        this->adjlist = adjlist;
    }
};

//kdtree traversal for constructing graphviz plot
void traverse(Node *root, vector<vector<double>> const &data, vector<graphvizNode *> &v, int &counter);
