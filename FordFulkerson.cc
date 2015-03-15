


//#include <time.h>
#include <queue>
#include "FordFulkerson.h"
#include <algorithm>


FordFulkerson::FordFulkerson(const Graph& g):edgeList(g.get_edgeList()),capList(g.get_capList()){
	n = g.get_num_nodes();
	numEdges = g.get_num_edges();
	color = 0;
	pred = 0;
	predEdge = 0;
	residualEdges = 0;
	firstEdge = 0;
	edgeTab = 0;
	construct_residual_graph();
}

FordFulkerson::~FordFulkerson(){
	delete [] color;
	delete [] pred;
	delete [] predEdge;
	delete [] firstEdge;
	delete [] edgeTab;
}

int FordFulkerson::min(int x, int y)
{
	return x<y ? x : y;  // returns minimum of x and y
}


// Breadth-First Search for an augmenting path

int FordFulkerson::bfs(int start, int target)
// Searches for path from start to target.
// Returns 1 if found, otherwise 0.
{
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
			if (color[v]==WHITE && edgeTab[i].capacity-edgeTab[i].flow>0)
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

// Ford-Fulkerson Algorithm

int FordFulkerson::max_flow(int source, int sink)
{
	int i,u;
	int max_flow;
	int APcount=0;

	try{
  		color = new int[n];
  		pred = new int[n];
  		predEdge = new int[n];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(1);
	}


// Initialize empty flow.
	max_flow = 0;
	for (i=0; i<residualEdges; i++)
	  edgeTab[i].flow=0;

// While there exists an augmenting path,
// increment the flow along this path.
	while (bfs(source,sink))
	{
  // Determine the amount by which we can increment the flow.
	  int increment = oo;
	  APcount++;
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
	  if (n<=20)
	  {
		// Path trace
		for (u=sink; pred[u]!=(-1); u=pred[u])
		  printf("%d<-",u);
		printf("%d adds %d incremental flow\n",source,increment);
	  }
	  max_flow += increment;
	}
	printf("%d augmenting paths\n",APcount);
// No more augmenting paths, so cut is based on reachability from last BFS.
	if (n<=20)
	{
	  printf("S side of min-cut:\n");
	  for (u=0; u<n; u++)
		if (color[u]==BLACK)
		  printf("%d\n",u);

	  printf("T side of min-cut:\n");
	  for (u=0; u<n; u++)
		if (color[u]==WHITE)
		  printf("%d\n",u);
	}

	return max_flow;
}


void FordFulkerson::dumpEdges(int count)
{
	int i;
	printf("  i tail head  cap\n");
	for (i=0; i<count; i++)
	  printf("%3d %3d  %3d %5d\n",i,edgeTab[i].tail,edgeTab[i].head,edgeTab[i].capacity);
}


void FordFulkerson::dumpFinal()
{
	int i;
	printf("Initialized residual network:\n");
	printf("Vertex firstEdge\n");
	for (i=0; i<n; i++)
	  printf(" %3d    %3d\n",i,firstEdge[i]);
	printf("=================\n");
	printf(" %3d    %3d\n",n,firstEdge[n]);

	printf("  i tail head  cap  inv\n");
	for (i=0; i<residualEdges; i++)
	  printf("%3d %3d  %3d %5d  %3d\n",i,edgeTab[i].tail,edgeTab[i].head,
		edgeTab[i].capacity,edgeTab[i].inverse);
}


int FordFulkerson::tailThenHead(const void* xin, const void* yin)
{	//compare function, used in sorting and binary search
	int result;
	edge *x,*y;

	x=(edge*) xin;
	y=(edge*) yin;
	result=x->tail - y->tail;
	if (result!=0)
	  return result;
	else
	  return x->head - y->head;
}


void FordFulkerson::construct_residual_graph(){

	if(edgeList==0 || capList==0){
		printf("reading graph from file failed %d\n",__LINE__);
		exit(5);
	}

	int workingEdges=0, tail, head, i, j;
	
	try{
  		if(edgeTab == 0) edgeTab = new edge[2*numEdges];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(2);
	}

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
	  edgeTab[workingEdges].capacity=0;
	  workingEdges++;
	}
	
	if (n<=20)
	{
	  printf("Input & inverses:\n");
	  dumpEdges(workingEdges);
	}	

	//qsort(edgeTab,workingEdges,sizeof(edge),tailThenHead);
	std::sort(edgeTab,edgeTab+workingEdges); //c++ type of sorting

	if (n<=20)
	{
	  printf("Sorted edges:\n");
	  dumpEdges(workingEdges);
	}

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
	
	if (n<=20)
	{
	  printf("Coalesced edges:\n");
	  dumpEdges(residualEdges);
	}

	edge inverse_edge, *ptr; 
	for (i=0; i<residualEdges; i++)
	{
	  inverse_edge.tail=edgeTab[i].head;
	  inverse_edge.head=edgeTab[i].tail;

	  //find the position of inverse edge in edge list
	  //ptr=(edge*) bsearch(&inverse_edge,edgeTab,residualEdges,sizeof(edge),tailThenHead);
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

	try{
  		if(firstEdge==0) firstEdge = new int[n+1];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(2);
	}

	j=0;
	for (i=0; i<n; i++)
	{
	  firstEdge[i]=j;
	  // Skip over edges with vertex i as their tail.
	  for ( ;j<residualEdges && edgeTab[j].tail==i;j++){}		
	}
	firstEdge[n]=residualEdges;  //Sentinel

	if (n<=20){
	  dumpFinal();
	}
}




