#include <stdio.h>
#include <queue>
#include <vector>
#include <utility> 
#include <unordered_map>
#include <iostream>
#include <cstdlib>
using namespace std;
//Basic Definitions

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000
typedef pair<int,int> IntPair;
typedef unordered_map<int, IntPair > neighbor_map;

//Declarations



int n;  // number of nodes
int e;  // number of edges
//int capacity[MAX_NODES][MAX_NODES]; // capacity matrix
neighbor_map neighbor[MAX_NODES];
//int flow[MAX_NODES][MAX_NODES];     // flow matrix
//vector<IntPair> flow[MAX_NODES];
int color[MAX_NODES]; // needed for breadth-first search               
int pred[MAX_NODES];  // array to store augmenting path

int min (int x, int y) {
    return x<y ? x : y;  // returns minimum of x and y
}


//A Queue for Breadth-First Search

// int head,tail;
// int q[MAX_NODES+2];

// void enqueue (int x) {
//     q[tail] = x;
//     tail++;
//     color[x] = GRAY;
// }

// int dequeue () {
//     int x = q[head];
//     head++;
//     color[x] = BLACK;
//     return x;
// }
//Breadth-First Search for an augmenting path

int bfs (int start, int target) {
    int u,v,dest,cap,flow;
    for (u=0; u<n; u++) {
	   color[u] = WHITE;
    }   

    color[start] = GRAY;
    queue<int> Q;
    Q.push(start);

    //head = tail = 0;
    //enqueue(start);
    pred[start] = -1;
    while (!Q.empty()) {
    	u = Q.front();
        Q.pop();
            // Search all adjacent white nodes v. If the capacity
            // from u to v in the residual network is positive,
            // enqueue v.
        neighbor_map::iterator it;
    	for (it=neighbor[u].begin(); it!=neighbor[u].end(); it++) {
            dest = (*it).first;
            cap = (*it).second.first;
            flow = (*it).second.second;

            //cout << dest << " " << cap << " " << flow << endl;
    	    if (color[dest]==WHITE && cap-flow>0) {
    		    color[dest] = GRAY;
                Q.push(dest);
    		    pred[dest] = u;
    	    }
    	}
        color[u] = BLACK;
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

//Ford-Fulkerson Algorithm





int max_flow (int source, int sink) {
    int i,j,u,cap,flow;
    // Initialize empty flow.
    int max_flow = 0; 
 //    for (i=0; i<n; i++) {
	// for (j=0; j<n; j++) {
	//     flow[i][j] = 0;
	// }
 //    }
    neighbor_map::iterator it;
    // for(i=0;i<n;i++){      
    //     for (it=graph[i].begin(); it!=graph[i].end(); it++) {
    //         (*it).second.second = 0;
    //     }
    // }

    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
        // Determine the amount by which we can increment the flow.
    	int increment = oo;
        
    	for (u = sink; pred[u]>=0 ; u=pred[u]) {
            cout << "u is " << u << endl;
            cout << "pred[u] is" << pred[u] << endl;
            it = neighbor[pred[u]].find(u);

            if(it == neighbor[pred[u]].end()){
                cout << "can't find" << endl;
                cout << "program will exit" << endl;
                exit(1);
            }

            cap = (*it).second.first;
            flow = (*it).second.second;
    	    increment = min(increment,cap-flow);
            cout << "this increment is" << increment << endl;
    	}
            // Now increment the flow.
    	for (u=sink; pred[u]>=0; u=pred[u]) {
            cout << "code comes here" << endl;

            it = neighbor[pred[u]].find(u);

            if(it != neighbor[pred[u]].end()){
                cout << "forward exists, increment flow" << endl;
                (*it).second.second += increment;
            }


            // it = neighbor[u].find(pred[u]);

            // if(it != neighbor[u].end()){
            //    (*it).second.second -= increment; 
            // }

    	    
    	}
    	max_flow += increment;
        }
    // No augmenting path anymore. We are done.
    return max_flow;
}
//Reading the input file and the main program

void read_input_file() {
    int a,b,c,i,j;
    FILE* input = fopen("mf.in","r");
    // read number of nodes and edges
    fscanf(input,"%d %d",&n,&e);
    // initialize empty capacity matrix 
 //    for (i=0; i<n; i++) {
	// for (j=0; j<n; j++) {
	//     capacity[i][j] = 0;
	// }
 //    }
    // read edge capacities
    for (i=0; i<e; i++) {
    	fscanf(input,"%d %d %d",&a,&b,&c);
    	//capacity[a][b] = c;
        //neighbor_map m(,)
        //cout << a << " " << b << " " << c << endl;
        neighbor[a].insert(pair<int, IntPair>(b, pair<int, int>(c,0)));
        //neighbor[b].insert(pair<int, IntPair>(a, pair<int, int>(c,0)));
    }
    fclose(input);



}

int main () {
    //int dest, cap, flow;
    read_input_file();

    // bfs(0,n-1);

    // for(int j=0; j<n;j++){
    //     cout << color[j] << endl;
    // }


    printf("%d\n",max_flow(0,n-1));
    // neighbor_map::iterator it;
    // for(int j=0; j<n; j++){
    //    for (it=neighbor[j].begin(); it!=neighbor[j].end(); it++) {
    //         dest = (*it).first;
    //         cap = (*it).second.first;
    //         flow = (*it).second.second;
    //         cout << dest << " " << cap << " " << flow << endl;      
    //     }
    // }
    return 0;
}