#include "binary.h"

#define INF INT_MAX

long long heap_size = 0; 
long long cap = 100000; 
vector<pair<long long,long long> > harr(cap); 

long long  parent(long long  i) { return (i-1)/2; } 
  
long long  left(long long  i) { return (2*i + 1); } 
 
long long  right(long long  i) { return (2*i + 2); } 

void MinHeapify(long long i);

void swap(pair<long long,long long> *x,pair<long long,long long> *y);

void insert_binary(pair<long long ,long long > p) 
{ 
    if (heap_size == cap) 
    { 
        cout << "\nOverflow: Could not insertKey\n"; 
        return; 
    } 
   
    heap_size++; 
    long long  i = heap_size - 1; 
    harr[i] = p; 
   
    while (i != 0 && harr[parent(i)].first > harr[i].first) 
    {  
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
void decreaseKey(long long i, long long new_val) 
{ 
    harr[i].first = new_val; 
    while (i != 0 && harr[parent(i)].first > harr[i].first) 
    { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
void extractMin() 
{ 
    if (heap_size <= 0) 
        return; 
    if (heap_size == 1) 
    { 
        heap_size--; 
        return; 
    } 
  
    harr[0].first = harr[heap_size-1].first;
    harr[0].second = harr[heap_size-1].second; 
    heap_size--; 
    MinHeapify(0); 
 
} 
  
void erase_binary(pair<long long, long long> p) 
{ 
    for(long long i=0;i<heap_size;i++)
	{
		if(harr[i].first==p.first && harr[i].second==p.second)
		{
			decreaseKey(i, INT_MIN); 
            extractMin();
			break;
		}
	}
} 
  
void MinHeapify(long long i) 
{ 
    long long l = left(i); 
    long long r = right(i); 
    long long smallest = i; 
    if (l < heap_size && harr[l].first < harr[i].first) 
        smallest = l; 
    if (r < heap_size && harr[r].first < harr[smallest].first) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 
   
void swap(pair<long long,long long> *x,pair<long long,long long> *y) 
{ 
    pair<long long,long long> temp = *x; 
    *x = *y; 
    *y = temp; 
} 

vector<long long> dijkstra_binary(list< pair<long long, long long> > *adj,long long V,long long src)
{  
    vector<long long> dist(V, INF); 

	long long nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;

    start = clock();
    insert_binary(make_pair(0, src)); 
    stop = clock();
    tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
    nins++;
    dist[src] = 0; 

    while (heap_size!=0) 
    { 
        pair<long long, long long> tmp = harr[0]; 
        start = clock(); 
        erase_binary(tmp); 
        stop = clock();
        terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;
  
        long long u = tmp.second; 
  
        list< pair<long long, long long> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
 
            long long v = (*i).first; 
            long long weight = (*i).second; 
  
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
	cout << "Per operation time "<< "insert " << tins/nins << " erase " << terase/nerase << endl;
    return dist;
}

void display_binary(vector<long long> dist,long long V)
{
    printf("Vertex   Distance from Source\n"); 
    for (long long i = 0; i < V; ++i) 
        printf("%lld \t\t %lld\n", i, dist[i]);
}