#include "Graph.h"
#include <algorithm>

Graph::Graph():n(0),numEdges(0),edgeList(0),capList(0){}

Graph::~Graph(){
	delete [] edgeList;
	delete [] capList;
}


int Graph::get_num_nodes() const{
	return n;
}

int Graph::get_num_edges() const{
	return numEdges;
}

int const * const Graph::get_edgeList() const{
	return edgeList;
}

int const * const Graph::get_capList() const{
	return capList;
}


void Graph::read_input_file(const std::string &filename){
	int tail,head,capacity,i;
	FILE* input = fopen(filename.c_str(),"r");
	
	// read number of nodes and edges
	fscanf(input,"%d %d",&n,&numEdges);
	
	try{
  		//edgeTab = new edge[2*numEdges];
  		edgeList = new int[2*numEdges];
  		capList = new int[numEdges];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(2);
	}

// read edges, each with a capacity

	for (i=0; i<numEdges; i++)
	{
	  fscanf(input,"%d %d %d",&tail,&head,&capacity);
	  // Test for illegal edge, including incoming to source and outgoing from
	  // sink.
	  if (tail<0 || tail>=n-1 || head<1 || head>=n || capacity<=0)
	  {
		printf("Invalid input %d %d %d at %d\n",tail,head,capacity,__LINE__);
		exit(3);
	  }

	  	edgeList[2*i] = tail;
	    edgeList[2*i+1] = head;
	    capList[i] = capacity;
	}
}






