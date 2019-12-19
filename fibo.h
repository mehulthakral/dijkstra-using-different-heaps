#include <bits/stdc++.h>

using namespace std;
 
struct node { 
    node* parent; 
    node* child; 
    node* left;  
    node* right; 
    int key; // weight of the edge
    int vertex; // Vertex
    int degree; 
    char mark; 
    char c; // Flag for assisting in the Find node function 
}; 

vector<int> dijkstra_fibonacci(list< pair<int, int> > *adj,int v,int src);
void display(vector<int> dist,int V);