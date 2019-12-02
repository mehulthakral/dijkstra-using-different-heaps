#include "fibo.h"
#include "binomial.h"
#include "binary.h"

using namespace std;

int main()
{
    int v,n,u,w,src,start,stop;
    cin >> v; //number of vertices
    list< pair<int, int> > *adj = new list< pair<int, int> >[v];
    cin >> src; // source vertex
    for(int i=0; i<v; i++)
    {
        cin >> n; //number of neighbours of i
        for(int j=0; j<n; j++)
        {
            cin >> u >> w; //vertex number, weight
            adj[i].push_back(make_pair(u,w));   
        }
    } 

    start = clock();
	vector<int> dist = dijkstra_fibonacci(adj,v,src);
	stop = clock();
    display_fibo(dist,v);
    cout << "Execution time using Fibonacci Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    // start = clock();
	// vector<int> dist_binomial = dijkstra_binomial(adj,v,src);
    // cerr << "here" << endl;
	// stop = clock();
    // display_binomial(dist_binomial,v);
    // cout << "Execution time using Binomial Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    start = clock();
	vector<int> dist_binary = dijkstra_binary(adj,v,src);
	stop = clock();
    display_binary(dist_binary,v);
    cout << "Execution time using Binary Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
    return 0;
}
