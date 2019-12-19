#include<stdio.h>
#include<stdlib.h>
#include "binary.h"

#define INF INT_MAX

Data A[1000];
int l=1;

void HeapBottomUp(Data * A, int n);
void Heapify(Data *A, int n, int k);

void HeapBottomUp(Data* A, int n)
{
	if(n <= 1) 
		return;
	for(int i=n/2;i>=1;i--)
		Heapify(A, n, i);
}

void Heapify(Data *A, int n, int k)
{
	Data temp;
	if(2*k > n) 
		return;
	int j = 2*k; 
	if(j+1 <= n)
		if(A[j+1].id > A[j].id) 
			j = j+1;
	if(A[j].id > A[k].id)
	{
		temp=A[j];
		A[j]=A[k];
		A[k]=temp;
		Heapify(A,n,j);
	}
}

void erase_binary(pair<int,int> p) 
{ 
    for(int i=1;i<=l;i++)
	{
		if(A[i].id==p.first)
		{
			A[i].id=A[l-1].id;
			A[i].value=A[l-1].value;
			HeapBottomUp(A,l);
			break;
		}
	}
	l--;
}

void insert_binary(pair<int,int> p) 
{ 
    A[l].id=p.first;
	A[l].value=p.second;
	l++;
	HeapBottomUp(A,l);
} 

vector<int> dijkstra_binary(list< pair<int, int> > *adj,int V,int src)
{  
    vector<int> dist(V, INF); 

	int nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;

    start = clock();
    insert_binary(make_pair(0, src)); 
    stop = clock();
    tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
    nins++;
    dist[src] = 0; 

    while (l!=1) 
    { 
        pair<int, int> tmp = make_pair(A[l-1].id,A[l-1].value); 
        start = clock(); 
        erase_binary(tmp); 
        stop = clock();
		terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;

        int u = tmp.second; 
  
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            if (dist[v] > dist[u] + weight) 
            { 
                if (dist[v] != INF) 
				{
					start = clock();
					erase_binary(make_pair(dist[v], v));
					stop = clock();
					terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
					nerase++;
				}
  
                dist[v] = dist[u] + weight; 
                start = clock(); 
                insert_binary(make_pair(dist[v], v));
                stop = clock();
                tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                nins++; 
            } 
        } 
    } 
	cout << "Per operation for binary: "<< "insert " << tins << " erase " << terase << endl;
    return dist;
}
