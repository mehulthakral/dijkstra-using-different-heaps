#include "binary.h"

using namespace std;

int main()
{
    long long v,n,d,u,w,src,e;
    int start,stop;
    char a;
    src = 1;
    cin >> v >> e;
    srand(time(0)); 
    list< pair<long long, long long> > *adj = new list< pair<long long, long long> >[v+1];
    for(long long i=0; i<e; i++)
    {
        cin >> a >> u >> d >> w; //vertex number, weight
        adj[u].push_back(make_pair(d,w));   
    } 

    cerr << "Done reading" << endl;

    start = clock();
	vector<long long> dist_binary = dijkstra_binary(adj,v+1,src);
	stop = clock();
    display_binary(dist_binary,v+1);
    cout << "Execution time using Binary Heap: " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
    return 0;
}
