#include <bits/stdc++.h>

using namespace std;
 
struct BNode 
{ 
    pair<int,int> data; 
    int degree; 
    BNode *parent, *child, *sibling; 
}; 

struct BHeap 
{ 
    list<BNode*> arr; 
}; 

BNode *createBNode(pair<int,int> key);
void swap(BNode *b1,BNode *b2);
BNode *mergeBHeaps(BNode *b1, BNode *b2);
list<BNode*> unionBHeaps(list<BNode*> l1,list<BNode*> l2);
void insert_binomial(struct BHeap *heap,pair<int,int> p);
void display(struct BHeap *heap);
void printTree(BNode *h);
void adjust(struct BHeap *heap);
pair<int, int> extractMin(struct BHeap *heap);
list<BNode*> removeMin(struct BHeap *heap,struct BNode *tree);
BNode* getMin(struct BHeap *heap);


vector<int> dijkstra_binomial(list< pair<int, int> > *adj,int v,int src);