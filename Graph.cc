#include "Graph.h"

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

double const * const Graph::get_capList() const{
	return capList;
}


void Graph::read_input_file(const std::string &filename){
	int tail,head,i;
	double capacity;
	 	
	FILE* input = fopen(filename.c_str(),"r");
	
	// read number of nodes and edges
	fscanf(input,"%d %d",&n,&numEdges);
	
	try{
  		edgeList = new int[4*numEdges];
  		capList = new double[2*numEdges];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(2);
	}

	

	// read edges, each with a capacity
	for (i=0; i<numEdges; i++)
	{
	  
	  fscanf(input,"%d %d %lf",&tail,&head,&capacity);
	  // Test for illegal edge, including incoming to source and outgoing from
	  // sink.
	  if (tail<0 || tail>=n-1 || head<1 || head>=n || capacity<=0)
	  {
		printf("Invalid input %d %d %lf at %d\n",tail,head,capacity,__LINE__);
		exit(3);
	  }
	  	// edgeList[2*i] = tail;
	   //  edgeList[2*i+1] = head;
	   //  capList[i] = capacity;
	  	edgeList[4*i] = tail;
	    edgeList[4*i+1] = head;
	    edgeList[4*i+2] = head;
	    edgeList[4*i+3] = tail;
	    capList[2*i] = capacity;
	    capList[2*i+1] = capacity;
	}
	numEdges = 2*numEdges;
	fclose(input);	//must CLOSE file object!!!!!!!

		
	// if(undirected){
	// 	numEdges = 2*numEdges;

	// try{
 //  		edgeList_tmp = new int[2*numEdges];
 //  		capList_tmp = new int[numEdges];
	// }
	// catch(std::bad_alloc& exc){
 //  		printf("memory allocation failed %d\n",__LINE__);
	//   	exit(2);
	// 	}
	// for(int j=0;j<numEdges/2;j++){
	// 	edgeList_tmp[4*j] = edgeList[2*j];
	// 	edgeList_tmp[4*j+1] = edgeList[2*j+1];
	// 	edgeList_tmp[4*j+2] = edgeList[2*j+1];
	// 	edgeList_tmp[4*j+3] = edgeList[2*j];
	// 	capList_tmp[2*j] = capList[j];
	// 	capList_tmp[2*j+1] = capList[j];
	// 	}
	// 	delete [] edgeList;
	// 	delete [] capList ;
	// 	edgeList = edgeList_tmp;
	// 	capList = capList_tmp;	

	// }
}








