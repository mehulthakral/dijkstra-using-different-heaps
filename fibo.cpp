#include "fibo.h"

#define INF INT_MAX

using namespace std;
 
struct node* root = NULL; 

int num_nodes = 0; 

void insert(pair<int,int> p) 
{ 
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
    new_node->key = p.first;
    new_node->vertex = p.second; 
    new_node->degree = 0; 
    new_node->mark = 'W'; 
    new_node->c = 'N'; 
    new_node->parent = NULL; 
    new_node->child = NULL; 
    new_node->left = new_node; 
    new_node->right = new_node; 
    if (root != NULL) { 
        (root->left)->right = new_node; 
        new_node->right = root; 
        new_node->left = root->left; 
        root->left = new_node; 
        if (new_node->key < root->key) 
            root = new_node; 
    } 
    else { 
        root = new_node; 
    } 
    num_nodes++; 
}

bool empty()
{
    return (root==NULL);
}

void Fibbo_link(struct node* ptr2, struct node* ptr1) 
{ 
    (ptr2->left)->right = ptr2->right; 
    (ptr2->right)->left = ptr2->left; 
    if (ptr1->right == ptr1) 
        root = ptr1; 
    ptr2->left = ptr2; 
    ptr2->right = ptr2; 
    ptr2->parent = ptr1; 
    if (ptr1->child == NULL) 
        ptr1->child = ptr2; 
    ptr2->right = ptr1->child; 
    ptr2->left = (ptr1->child)->left; 
    ((ptr1->child)->left)->right = ptr2; 
    (ptr1->child)->left = ptr2; 
    if (ptr2->key < (ptr1->child)->key) 
        ptr1->child = ptr2; 
    ptr1->degree++; 
} 
 
void Consolidate() 
{ 
    int temp1; 
    float temp2 = (log(num_nodes)) / (log(2)); 
    int temp3 = temp2; 
    struct node* arr[temp3]; 
    for (int i = 0; i <= temp3; i++) 
        arr[i] = NULL; 
    node* ptr1 = root; 
    node* ptr2; 
    node* ptr3; 
    node* ptr4 = ptr1; 
    do { 
        ptr4 = ptr4->right; 
        temp1 = ptr1->degree; 
        while (arr[temp1] != NULL) { 
            ptr2 = arr[temp1]; 
            if (ptr1->key > ptr2->key) { 
                ptr3 = ptr1; 
                ptr1 = ptr2; 
                ptr2 = ptr3; 
            } 
            if (ptr2 == root) 
                root = ptr1; 
            Fibbo_link(ptr2, ptr1); 
            if (ptr1->right == ptr1) 
                root = ptr1; 
            arr[temp1] = NULL; 
            temp1++; 
        } 
        arr[temp1] = ptr1; 
        ptr1 = ptr1->right; 
    } while (ptr1 != root); 
    root = NULL; 
    for (int j = 0; j <= temp3; j++) { 
        if (arr[j] != NULL) { 
            arr[j]->left = arr[j]; 
            arr[j]->right = arr[j]; 
            if (root != NULL) { 
                (root->left)->right = arr[j]; 
                arr[j]->right = root; 
                arr[j]->left = root->left; 
                root->left = arr[j]; 
                if (arr[j]->key < root->key) 
                    root = arr[j]; 
            } 
            else { 
                root = arr[j]; 
            } 
            if (root == NULL) 
                root = arr[j]; 
            else if (arr[j]->key < root->key) 
                root = arr[j]; 
        } 
    } 
} 
  
void Extract_min() 
{ 
    if (root == NULL) 
        cout << "The heap is empty" << endl; 
    else { 
        node* temp = root; 
        node* ptr; 
        ptr = temp; 
        node* x = NULL; 
        if (temp->child != NULL) { 
  
            x = temp->child; 
            do { 
                ptr = x->right; 
                (root->left)->right = x; 
                x->right = root; 
                x->left = root->left; 
                root->left = x; 
                if (x->key < root->key) 
                    root = x; 
                x->parent = NULL; 
                x = ptr; 
            } while (ptr != temp->child); 
        } 
        (temp->left)->right = temp->right; 
        (temp->right)->left = temp->left; 
        root = temp->right; 
        if (temp == temp->right && temp->child == NULL) 
            root = NULL; 
        else { 
            root = temp->right; 
            Consolidate(); 
        } 
        num_nodes--; 
    } 
} 
  
 
void Cut(struct node* found, struct node* temp) 
{ 
    if (found == found->right) 
        temp->child = NULL; 
  
    (found->left)->right = found->right; 
    (found->right)->left = found->left; 
    if (found == temp->child) 
        temp->child = found->right; 
  
    temp->degree = temp->degree - 1; 
    found->right = found; 
    found->left = found; 
    (root->left)->right = found; 
    found->right = root; 
    found->left = root->left; 
    root->left = found; 
    found->parent = NULL; 
    found->mark = 'B'; 
} 
   
void Cascade_cut(struct node* temp) 
{ 
    node* ptr = temp->parent; 
    if (ptr != NULL) { 
        if (temp->mark == 'W') { 
            temp->mark = 'B'; 
        } 
        else { 
            Cut(temp, ptr); 
            Cascade_cut(ptr); 
        } 
    } 
}
 
void Decrease_key(struct node* found, int val) 
{ 
    if (root == NULL) 
        cout << "The Heap is Empty" << endl; 
  
    if (found == NULL) 
        cout << "Node not found in the Heap" << endl; 
  
    found->key = val; 
  
    struct node* temp = found->parent; 
    if (temp != NULL && found->key < temp->key) { 
        Cut(found, temp); 
        Cascade_cut(temp); 
    } 
    if (found->key < root->key) 
        root = found; 
} 

void Find(struct node* root, pair<int,int> p, int val) 
{ 
    struct node* found = NULL; 
    node* temp = root; 
    temp->c = 'Y'; 
    node* found_ptr = NULL; 
    if (temp->key == p.first && temp->vertex == p.second) { 
        found_ptr = temp; 
        temp->c = 'N'; 
        found = found_ptr; 
        Decrease_key(found, val); 
    } 
    if (found_ptr == NULL) { 
        if (temp->child != NULL) 
            Find(temp->child, p, val); 
        if ((temp->right)->c != 'Y') 
            Find(temp->right, p, val); 
    } 
    temp->c = 'N'; 
    found = found_ptr; 
} 
 
void erase(pair<int,int> p) 
{ 
    if (root == NULL) 
        cout << "The heap is empty" << endl; 
    else { 
        
        Find(root, p, 0); 
        Extract_min(); 
    } 
} 

vector<int> dijkstra_fibonacci(list< pair<int, int> > *adj,int V,int src)
{  
    vector<int> dist(V, INF); 

    int nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;

    start = clock();
    insert(make_pair(0, src)); 
    stop = clock();
    tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
    nins++;
    dist[src] = 0; 

    while (!empty()) 
    { 
        pair<int, int> tmp = make_pair(root->key,root->vertex);
        start = clock(); 
        erase(tmp); 
        stop = clock();
        terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;
        // dist[src] = 0;
  
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
                    erase(make_pair(dist[v], v));
                    stop = clock();
                    terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                    nerase++;
                }  
  
                dist[v] = dist[u] + weight;
                start = clock(); 
                insert(make_pair(dist[v], v));
                // cerr << "after insert" << endl; 
                stop = clock();
                tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                nins++;
            } 
        } 
    } 

    cout << "insert " << tins << " erase " << terase << endl;
    return dist;
}

void display_fibo(vector<int> dist,int V)
{
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < V; ++i) 
        printf("%d \t\t %d\n", i, dist[i]);
}