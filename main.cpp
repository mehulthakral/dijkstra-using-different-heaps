#include "fibo.h"

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
    fibo_display(dist,v);
    cout << "Execution time using Fibonacci Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
    
    // start = clock();
	// dijkstra_binomial(adj,v,src);
	// stop = clock();
    // binomial_display();
    // cout << "Execution time using Binomial Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    // start = clock();
	// dijkstra_binary(adj,v,src);
	// stop = clock();
    // binary_display();
    // cout << "Execution time using Binary Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
    return 0;
}
