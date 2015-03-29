
#include <queue>
#include "FordFulkerson.h"


FordFulkerson::FordFulkerson(const Graph& g):n(g.get_g_star_prime_num_nodes()),
							numEdges(g.get_g_star_prime_num_edges()),
							edgeList(g.get_edgeList()),capList(g.get_capList()){
	residualEdges = 0;
	try{
  		color = new int[n];
  		pred = new int[n];
  		predEdge = new int[n];
		nodeList = new node[n];
		edgeTab = new edge[2*numEdges];
		firstEdge = new int[n+1];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(1);
	}

	construct_residual_graph();	//construct residual graph

	for(int i=0; i<n;i++)	//set node id 
		nodeList[i].id = i;
}

FordFulkerson::~FordFulkerson(){
	delete [] color;
	delete [] pred;
	delete [] predEdge;
	delete [] firstEdge;
	delete [] edgeTab;
	delete [] nodeList;
}

double FordFulkerson::min(double x, double y)
{
	return x<y ? x : y;  // returns minimum of x and y
}

/*
* nodelist store the S-T cut information
*/
node *FordFulkerson::get_nodeList(){
	return nodeList;	
}


/*
* Breadth-First Search for an augmenting path
* Searches for path from start to target
* Returns 1 if found, otherwise 0.
*/
int FordFulkerson::bfs(int start, int target){
	int u,v,i;
    for (u=0; u<n; u++) {
   		color[u] = WHITE;
	}   

    color[start] = GRAY;
    std::queue<int> Q;
    Q.push(start);
	pred[start] = -1;
	
    while (!Q.empty()) {
    	u = Q.front();
        Q.pop();
		 
		  // Search all adjacent white nodes v. If the residual capacity
		  // from u to v in the residual network is positive,
		  // enqueue v.
		for (i=firstEdge[u]; i<firstEdge[u+1]; i++){
			v=edgeTab[i].head;
			if (color[v]==WHITE && edgeTab[i].capacity-edgeTab[i].flow>0.0)
			{
			  Q.push(v);
			  pred[v] = u;
			  predEdge[v]=i;
			}
		  }
		  //all u's neighbors have been visited
		  color[u] = BLACK;
		}
		
		// No augmenting path remains, so a maximum flow and minimum cut
		// have been found.  Black vertices are in the
		// source side (S) of the minimum cut, while white vertices are in the
		// sink side (T).	
	return color[target]==BLACK;
}


// implementation of Ford-Fulkerson Algorithm
double FordFulkerson::max_flow(int source, int sink)
{
	int i,u;
	double max_flow;

	// Initialize empty flow.
	max_flow = 0.0;
	for (i=0; i<residualEdges; i++)
	  edgeTab[i].flow=0.0;

	// While there exists an augmenting path,
	// increment the flow along this path.
	while (bfs(source,sink))
	{
  		// Determine the amount by which we can increment the flow.
	  double increment = oo;
	  for (u=sink; pred[u]!=(-1); u=pred[u])
	  {
		i=predEdge[u];
		increment = min(increment,edgeTab[i].capacity-edgeTab[i].flow);
	  }
	// Now increment the flow.
	  for (u=sink; pred[u]!=(-1); u=pred[u])
	  {
		i = edgeTab[predEdge[u]].inverse;
		edgeTab[predEdge[u]].flow += increment;
		edgeTab[i].flow -= increment;  // Reverse in residual
	  }
	  max_flow += increment;
	}

	// No more augmenting paths, so cut is based on reachability from last BFS.
	//set cut set of S and T
	for (int u=0; u<n; u++){
		nodeList[u].s_side = false; //must do! reset s_side to false
		if(color[u]==BLACK){
		  nodeList[u].s_side = true; //if 
		}
	}	
	return max_flow;
}

void FordFulkerson::construct_residual_graph(){

	if(edgeList==0 || capList==0){
		printf("Ford-Fulkerson::reading graph from g_star failed %d\n",__LINE__);
		return;
	}

	int workingEdges=0, tail, head, i, j;
	
	for (i=0; i<numEdges; i++)
	{
	  tail = edgeList[2*i];	
	  head = edgeList[2*i+1];
	  
	  // Save input edge
	  edgeTab[workingEdges].tail=tail;
	  edgeTab[workingEdges].head=head;
	  edgeTab[workingEdges].capacity=capList[i];
	  workingEdges++;
	  // Save inverse of input edge
	  edgeTab[workingEdges].tail=head;
	  edgeTab[workingEdges].head=tail;
	  edgeTab[workingEdges].capacity=0.0;
	  workingEdges++;
	}

	std::sort(edgeTab,edgeTab+workingEdges); //c++ type of sorting

	for (i=1; i<workingEdges; i++)
	  if (edgeTab[residualEdges].tail==edgeTab[i].tail
	  &&  edgeTab[residualEdges].head==edgeTab[i].head)
		edgeTab[residualEdges].capacity+=edgeTab[i].capacity;  // || case
	  else
	  {
		residualEdges++;
		edgeTab[residualEdges].tail=edgeTab[i].tail;
		edgeTab[residualEdges].head=edgeTab[i].head;
		edgeTab[residualEdges].capacity=edgeTab[i].capacity;
	  }
	residualEdges++;
	
	edge inverse_edge, *ptr; 
	for (i=0; i<residualEdges; i++)
	{
	  inverse_edge.tail=edgeTab[i].head;
	  inverse_edge.head=edgeTab[i].tail;

	  //find the position of inverse edge in edge list
	  ptr = std::lower_bound(edgeTab, edgeTab+residualEdges,inverse_edge);

	  if (ptr==NULL)
	  {
		printf("bsearch %d failed %d\n",i,__LINE__);
		exit(4);
	  }
	  edgeTab[i].inverse=ptr-edgeTab;  // ptr arithmetic to get subscript
	}

	// For each vertex i, determine first edge in edgeTab with
	// a tail >= i.
	j=0;
	for (i=0; i<n; i++)
	{
	  firstEdge[i]=j;
	  // Skip over edges with vertex i as their tail.
	  for ( ;j<residualEdges && edgeTab[j].tail==i;j++){}		
	}
	firstEdge[n]=residualEdges;  //Sentinel	
}




