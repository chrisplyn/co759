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
			//std::cout << " ==== " << "x_star is not integral, a matching is not found!!!!!!" << " ==== " << std::endl;
			return false;
		}
	}
	//std::cout << "a matching is found!!!!!!" << std::endl;
	return true;	
}

void Graph::construct_g_star(){
	/*
	this function constructs G* based on X* 
	*/
	//~ std::cout << " ==== " << "contruct graph g_star based on lp solution x_star" << "====" << std::endl;
	//~ std::cout << std::endl;
	
	int const * G_edgeList = rlp->get_edgeList();
	int origin, dest;	
	if(adjacencyList == 0) adjacencyList = new set[n]; 
	if(visited == 0) visited = new bool[n]();

	for (int j = 0; j < G_numEdges; j++) {
		if (lp_sol[j] > LP_EPSILON){			
			origin =  G_edgeList[2*j];
			dest = G_edgeList[2*j+1];			
			adjacencyList[origin].insert(dest);
			adjacencyList[dest].insert(origin);
			numEdges++; 			
		}
	}
	//std::cout << " ==== " << "g_star has " << numEdges << " edges" << " ==== " << std::endl;
	//DFS::print_adjacencyList(n, adjacencyList);
}


/*
 * Based lp solution x_star, 
 */ 
std::vector<Component> Graph::find_odd_cut_set(){

	std::vector<Component> odd_cut_set; 
	
	if(!components.empty()) components.clear();		
	for(int j=0; j<n;j++){
		visited[j] = false;
	}
	
	//~ std::cout << " ==== " << "perform depth first search on g_star" << " ==== " << std::endl;
	//~ std::cout << " ==== " << "find connected components of odd size on g_star" << " ==== " << std::endl;

	DFS::find_connected_components(n, adjacencyList, visited, components);
	
	//std::cout << " ==== " << "g_star has " << components.size() << " connected components" << std::endl;
	
	if(components.size()!=1){ 		
		for (auto it=components.begin();it!=components.end();++it){    			   
			if((*it).size() % 2 != 0){
				//DFS::print_component(*it); 
				odd_cut_set.push_back(*it);						
			}    
		}
	}	
	return odd_cut_set;
}



void Graph::convert_g_star(){
	
	int origin,dest,i,j;
	int const * G_edgeList = rlp->get_edgeList();
 	
	//std::cout << " ==== " << "g_star has " << numEdges << " edges" << " ==== " << std::endl;

	try{
  		edgeList = new int[4*numEdges];
  		capList = new double[2*numEdges];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	exit(2);
	}


		for (i = 0,j=0; i < G_numEdges; i++) {

			
	  	if (lp_sol[i] > LP_EPSILON){			
			origin =  G_edgeList[2*i];
			dest = G_edgeList[2*i+1];			
			
			
			edgeList[4*j] = origin;
			edgeList[4*j+1] = dest;
			edgeList[4*j+2] = dest;
			edgeList[4*j+3] = origin;
			capList[2*j] = lp_sol[i];
			capList[2*j+1] = lp_sol[i];
			j++;
		}
	}
	numEdges = 2*numEdges;	

}		
	






