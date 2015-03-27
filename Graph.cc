#include "Graph.h"
#include <iostream>

Graph::Graph(RelaxedLP &rlp):rlp(&rlp),n(rlp.get_num_nodes()),
			edgeList(0),capList(0),adjacencyList(0),G_numEdges(rlp.get_num_edges()),
			lp_sol(rlp.get_relaxed_lp_sol()),visited(0), G_edgeList(rlp.get_edgeList()){
				num_g_prime_Edges = 0;
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


const Bimap& Graph::get_g_prime_node_map() const{
	return map;	
}

int Graph::get_g_prime_num_nodes() const{
	return map.get_size();
}

int Graph::get_g_prime_num_edges() const{
	return num_g_prime_Edges;
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
	std::cout << "a matching is found!!!!!!" << std::endl;
	return true;	
}


void Graph::construct_adjacencyList(double rhs, int& num_g_star_Edges, int& num_g_prime_Edges, int G_numEdges, const int* G_edgeList, double *lp_sol, set *adjacencyList){
	int origin, dest;
	for (int j = 0; j < G_numEdges; j++) {
		if (lp_sol[j] > rhs){			
			origin =  G_edgeList[2*j];
			dest = G_edgeList[2*j+1];			
			adjacencyList[origin].insert(dest);
			adjacencyList[dest].insert(origin);
			num_g_star_Edges++;
			if(lp_sol[j] < 1.0 - LP_EPSILON) num_g_prime_Edges++; 			
		}
	}		
}


void Graph::construct_graph(double rhs){
	/*
	this function constructs G* based on X* 
	*/
	destruct();
	adjacencyList = new set[n]; 
	visited = new bool[n]();
	num_g_prime_Edges = 0;
	construct_adjacencyList(rhs, num_g_star_Edges, num_g_prime_Edges, G_numEdges, G_edgeList, lp_sol, adjacencyList);
}


void Graph::construct_g_star(){
	construct_graph(LP_EPSILON);
	std::cout << "G* has " << num_g_star_Edges << " edges" << std::endl;
	std::cout << "G'has " << num_g_prime_Edges << " edges" << std::endl;
}


void Graph::construct_g_star_2(){
	construct_graph(0.3);
}



/*
 * Based on lp solution x_star, 
 */ 
std::vector<Component> Graph::find_odd_cut_set(){
	
	std::vector<Component> odd_cut_set; 	
	if(!components.empty()) components.clear();		
	for(int j=0; j<n;j++){
		visited[j] = false;
	}	
	
	DFS::find_connected_components(n, adjacencyList, visited, components);
		
	if(components.size()!=1){ 		
		for (auto it=components.begin();it!=components.end();++it){    			   
			if((*it).size() % 2 != 0){
				odd_cut_set.push_back(*it);						
			}    
		}
	}	
	return odd_cut_set;
}



void Graph::construct_g_star_prime(){
	
	int origin,dest,i,j,new_orig,new_dest; 	
	try{
  		edgeList = new int[4*num_g_prime_Edges];
  		capList = new double[2*num_g_prime_Edges];
	}
	catch(std::bad_alloc& exc){
  		printf("memory allocation failed %d\n",__LINE__);
	  	destruct();
	  	exit(2);
	}

	/*
	 * construct directed graph based on undirected graph, the number of edges in G' will be doubled
	 */
	 
	for (i = 0,j=0; i < G_numEdges; i++) {
		
		if ( lp_sol[i] > LP_EPSILON && lp_sol[i] < 1.0 - LP_EPSILON){
			
			//std::cout <<  lp_sol[i] << std::endl;			
			origin =  G_edgeList[2*i];
			dest = G_edgeList[2*i+1];									
						
			new_orig = map.add(origin);
			new_dest = map.add(dest);
						
			edgeList[4*j] = new_orig;
			edgeList[4*j+1] = new_dest;
			edgeList[4*j+2] = new_dest;
			edgeList[4*j+3] = new_orig;
			capList[2*j] = lp_sol[i];
			capList[2*j+1] = lp_sol[i];
			j++;
			}
		}
	num_g_prime_Edges = 2*num_g_prime_Edges;	
}		
	






