#include "Graph.h"
#include <iostream>

Graph::Graph(RelaxedLP &rlp):rlp(&rlp),n(rlp.get_num_nodes()),numEdges(0),
			edgeList(0),capList(0),adjacencyList(0),G_numEdges(rlp.get_num_edges()),
			lp_sol(rlp.get_relaxed_lp_sol()),visited(0){
}


Graph::~Graph(){
	destruct();
}


void Graph::destruct(){
	if (edgeList!=0) delete [] edgeList;
	if (capList!=0) delete [] capList;
	if (adjacencyList!=0) delete [] adjacencyList;
	if (visited!=0) delete [] visited;
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


bool Graph::check_integrality(){
	for (int j=0; j < G_numEdges; ++j) {
		if (lp_sol[j] > LP_EPSILON && lp_sol[j] < 1.0 - LP_EPSILON){
			return false;
		}
	}
	return true;	
}

void Graph::construct_g_star(){
	/*
	this function constructs G* based on X* 
	*/
		
	int const * G_edgeList = rlp->get_edgeList();
	int origin, dest;	
	adjacencyList = new set[n]; 
	visited = new bool[n]();

	
	for (int j = 0; j < G_numEdges; j++) {
		if (lp_sol[j] > LP_EPSILON){			
			origin =  G_edgeList[2*j];
			dest = G_edgeList[2*j+1];			
			adjacencyList[origin].insert(dest);
			adjacencyList[dest].insert(origin);
			numEdges++; 
			
		}
	}
	std::cout << "G* has " << numEdges << " edges" << std::endl;
	DFS::print_adjacencyList(n, adjacencyList);
}



std::vector<Component> Graph::find_odd_cut_set(){

	Graph::construct_g_star();
	std::vector<Component> odd_cut_set; 
	
	if(!components.empty()) components.clear();		
	for(int j=0; j<n;j++){
		visited[j] = false;
	}
	
	DFS::find_connected_components(n, adjacencyList, visited, components);
	
	for (auto it1=components.begin();it1!=components.end();++it1){        
        if((*it1).size() % 2 != 0){
			odd_cut_set.push_back(*it1);						
		}    
   	}
	return odd_cut_set;
}

//~ void Graph::read_input_file(const std::string &filename){
	//~ int tail,head,i;
	//~ double capacity;
	 	//~ 
	//~ FILE* input = fopen(filename.c_str(),"r");
	//~ 
	//~ // read number of nodes and edges
	//~ fscanf(input,"%d %d",&n,&numEdges);
	//~ 
	//~ try{
  		//~ edgeList = new int[4*numEdges];
  		//~ capList = new double[2*numEdges];
	//~ }
	//~ catch(std::bad_alloc& exc){
  		//~ printf("memory allocation failed %d\n",__LINE__);
	  	//~ exit(2);
	//~ }
//~ 
	//~ 
	//~ // read edges, each with a capacity
	//~ for (i=0; i<numEdges; i++)
	//~ {
	  //~ 
	  //~ fscanf(input,"%d %d %lf",&tail,&head,&capacity);
	  //~ // Test for illegal edge, including incoming to source and outgoing from
	  //~ // sink.
	  //~ if (tail<0 || tail>=n-1 || head<1 || head>=n || capacity<=0)
	  //~ {
		//~ printf("Invalid input %d %d %lf at %d\n",tail,head,capacity,__LINE__);
		//~ exit(3);
	  //~ }
	  	//~ // edgeList[2*i] = tail;
	   //~ //  edgeList[2*i+1] = head;
	   //~ //  capList[i] = capacity;
	  	//~ edgeList[4*i] = tail;
	    //~ edgeList[4*i+1] = head;
	    //~ edgeList[4*i+2] = head;
	    //~ edgeList[4*i+3] = tail;
	    //~ capList[2*i] = capacity;
	    //~ capList[2*i+1] = capacity;
	//~ }
	//~ numEdges = 2*numEdges;
	//~ fclose(input);	//must CLOSE file object!!!!!!!
//~ 
		//~ 
	//~ // if(undirected){
	//~ // 	numEdges = 2*numEdges;
//~ 
	//~ // try{
 //~ //  		edgeList_tmp = new int[2*numEdges];
 //~ //  		capList_tmp = new int[numEdges];
	//~ // }
	//~ // catch(std::bad_alloc& exc){
 //~ //  		printf("memory allocation failed %d\n",__LINE__);
	//~ //   	exit(2);
	//~ // 	}
	//~ // for(int j=0;j<numEdges/2;j++){
	//~ // 	edgeList_tmp[4*j] = edgeList[2*j];
	//~ // 	edgeList_tmp[4*j+1] = edgeList[2*j+1];
	//~ // 	edgeList_tmp[4*j+2] = edgeList[2*j+1];
	//~ // 	edgeList_tmp[4*j+3] = edgeList[2*j];
	//~ // 	capList_tmp[2*j] = capList[j];
	//~ // 	capList_tmp[2*j+1] = capList[j];
	//~ // 	}
	//~ // 	delete [] edgeList;
	//~ // 	delete [] capList ;
	//~ // 	edgeList = edgeList_tmp;
	//~ // 	capList = capList_tmp;	
//~ 
	//~ // }
//~ }
//~ 
//~ 






