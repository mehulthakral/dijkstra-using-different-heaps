#include<stdio.h> 
#include<stdlib.h> 
#include "binomial.h"
#include <bits/stdc++.h> 
using namespace std; 

#define INF INT_MAX
  
BNode *createBNode(pair<int,int> key) 
{ 
    BNode *new_node = new BNode; 
    new_node->data = key;
    new_node->parent = NULL; 
    new_node->sibling = NULL; 
    new_node->child = NULL; 
    new_node->degree = 0; 
    return new_node; 
} 

void swap(BNode *b1,BNode *b2)
{
    BNode *a;
    a=b1;
    b1=b2;
    b2=a;
}
  
BNode *mergeBHeaps(BNode *b1, BNode *b2) 
{ 
    if ((b1->data).first > (b2->data).first)
    {
        swap(b1, b2);
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1; 
} 
  
list<BNode*> unionBHeaps(list<BNode*> l1,list<BNode*> l2) 
{ 
    list<BNode*> _new;
    list<BNode*>::iterator it = l1.begin();
    list<BNode*>::iterator ot = l2.begin();
    while (it!=l1.end() && ot!=l2.end())
    {
        if((*it)->degree <= (*ot)->degree)
        {
            _new.push_back(*it);
            it++;
        }
        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }
    while (it != l1.end())
    {
        _new.push_back(*it);
        it++;
    }
    while (ot!=l2.end())
    {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
} 
  
void insert_binomial(struct BHeap *heap,pair<int,int> p) 
{ 
    BNode *tree = createBNode(p);
    list<BNode*> temp;
    temp.push_back(tree);
    heap->arr = unionBHeaps(heap->arr,temp);
    adjust(heap); 
} 

void adjust(struct BHeap *heap)
{
    if (heap->arr.size() <= 1)
        return;
    list<BNode*> new_heap;
    list<BNode*>::iterator it1,it2,it3;
    it1 = it2 = it3 = heap->arr.begin();

    if (heap->arr.size() == 2)
    {
        it2 = it1;
        it2++;
        it3 = heap->arr.end();
    }
    else
    {
        it2++;
        it3=it2;
        it3++;
    }
    while (it1 != heap->arr.end())
    {
        if (it2 == heap->arr.end())
            it1++;
        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if(it3!=heap->arr.end())
                it3++;
        }
        else if (it3!=heap->arr.end() &&
                (*it1)->degree == (*it2)->degree &&
                (*it1)->degree == (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }
        else if ((*it1)->degree == (*it2)->degree)
        {
            *it1 = mergeBHeaps(*it1,*it2);
            it2 = heap->arr.erase(it2);
            if(it3 != heap->arr.end())
                it3++;
        }
    }
    return;
}

pair<int, int> extractMin(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);
    list<BNode*> new_heap,lo;
    BNode *temp;
    temp = getMin(heap);
    list<BNode*>::iterator it;
    it = heap->arr.begin();
    while (it != heap->arr.end())
    {
        if (*it != temp)
        {
            new_heap.push_back(*it);
        }
        it++;
    }
    lo=removeMin(heap,temp);
    heap->arr = unionBHeaps(new_heap,lo);
    adjust(heap);
    return temp->data;
}
  
list<BNode*> removeMin(struct BHeap *heap,struct BNode *tree)
{
    list<BNode*> tempheap;
    BNode *temp = tree->child;
    BNode *lo;
    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        tempheap.push_front(lo);
    }
    return tempheap;
}

BNode* getMin(struct BHeap *heap)
{
    if (heap->arr.size() == 0)
        return NULL;
    list<BNode*>::iterator it = heap->arr.begin();
    BNode *temp = *it;
    while (it != heap->arr.end())
    {
        if (((*it)->data).first < (temp->data).first)
            temp = *it;
        it++;
    }
    return temp;
}

pair<int, int> top(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);

    return getMin(heap)->data;
}

pair<int, int> pop(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);

    pair<int, int> BNode = extractMin(heap);
    return BNode;
}

vector<int> dijkstra_binomial(list< pair<int, int> > *adj,int V,int src)
{  
    struct BHeap heap;
    int nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;
    vector<int> dist(V, INF); 
    start = clock();
    insert_binomial(&heap,make_pair(0, src)); 
    stop = clock();
    tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
    nins++;
    dist[src] = 0; 

    while (top(&heap) != make_pair(-1, -1)) 
    { 
        int u = top(&heap).second; 
        start = clock(); 
        pop(&heap);
        stop = clock();
        terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;
  
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            if (dist[v] > dist[u] + weight) 
            { 
                dist[v] = dist[u] + weight; 
		start = clock(); 
                insert_binomial(&heap,make_pair(dist[v], v)); 
                stop = clock();
                tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                nins++;
            } 
        } 
    } 
    cout << "Per operation for binomial: "<<"insert " << tins << " erase " << terase << endl;
    return dist;
}
