#include <bits/stdc++.h>

using namespace std;
 

typedef struct Data
{
	int id;
	int value;
} Data;

vector<int> dijkstra_binary(list< pair<int, int> > *adj,int v,int src);
