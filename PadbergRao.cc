#include "PadbergRao.h"
#include "DFS.h"
#include <iomanip> 

PadbergRao::PadbergRao(Graph &g):gh(new GomoryHu(g)),numNodes(g.get_g_star_prime_num_nodes()),
	g_prime_node_map(g.get_g_prime_node_map()){
		
	nl = gh->construct_GH_tree();
	std::sort(nl,nl+numNodes);	//sort Gomory-Hu tree edges according to its capacity

	adjacencyList = new set[numNodes];
	construct_gh_tree_adjacencyList(); //construct Gomory-Hu tree's adjacency list

    visited = new bool[numNodes]();	//used for DFS
}

PadbergRao::~PadbergRao(){
	delete gh;
	delete [] adjacencyList;
	delete [] visited;
}


void PadbergRao::print_gh_tree(){
	for(int i=0; i<numNodes; i++){
		std::cout << nl[i].id << " " << nl[i].parent << " " << std::setprecision(6) << nl[i].mincap << std::endl;
	}
}


void PadbergRao::construct_gh_tree_adjacencyList(){
	if(adjacencyList!=0){
		delete [] adjacencyList;
		adjacencyList = new set[numNodes]; 
	}

    int origin,destination;
    for (int i = 1; i < numNodes; i++) {
       	origin = nl[i].id;
        destination = nl[i].parent;        
        adjacencyList[origin].insert(destination);
        adjacencyList[destination].insert(origin);
    }
}	



void PadbergRao::add_constraint(RelaxedLP &rlp){
	int i,origin,destination;
	
	for(i=0; i<numNodes; i++){
		//reconstruct graph, reset components and visited to inital status	 
		
		if(nl[i].mincap > 1-LP_EPSILON) break;
		origin = nl[i].id;
		destination = nl[i].parent;  
		if(origin == destination) continue;

		   
		if(!components.empty()) components.clear();		
		for(int j=0; j<numNodes;j++){
			visited[j] = false;
		}

		//remove one edge from GH tree           
		adjacencyList[origin].erase(destination);
		adjacencyList[destination].erase(origin);	
		
		//perform depth first search on modified GH-tree
		DFS::find_connected_components(numNodes, adjacencyList, visited, components);
		
		if(components.size()!=2){
			std::cout << "WRONG component number!!!! " << std::endl;
			break;
		}	
			
		add_constraint_util(components, rlp);	
        
        // restore original adjacency list
		adjacencyList[origin].insert(destination);
        adjacencyList[destination].insert(origin);
	}
}


/*
* helper function, find the smaller components after removing one edge from original GH-tree
* then adding corresponding contraints to the relaxed lp problem
*/
void PadbergRao::add_constraint_util(std::vector<Component>& components, RelaxedLP& rlp){
	unsigned int tmp = oo,i=0;	
	for (auto it=components.begin();it!=components.end();++it){    			   
		if((*it).size() % 2 != 0 && (*it).size() != 1){	 //only consider components have odd size					
			if(tmp > (*it).size()){
				tmp = (*it).size();
				i++;	 //find smaller component
			}	 	
		}else{
			return;
		}    
	}
	
	//map new node in the smaller component back to old node 
	for(auto it = components[i-1].begin(); it != components[i-1].end(); it++)
		*it = g_prime_node_map.get(*it);
	
	//find gamma corresponding to the smaller conponent, then add it to the relaxed lp
	std::vector<int> gamma = Heuristics1::findGamma(components[i-1], rlp); 	
	int rval = Heuristics1::add_constraint_util(gamma,components[i-1].size(),rlp);    
    
	if(rval){
		fprintf(stderr, "add_constraint failed"); return;
	}
			
}





