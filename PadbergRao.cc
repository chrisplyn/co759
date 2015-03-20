#include "PadbergRao.h"
#include "DFS.h"


PadbergRao::PadbergRao(Graph &g):gh(new GomoryHu(g)),numNodes(g.get_num_nodes()){
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
	for(int i=1; i<numNodes; i++){
		std::cout << nl[i].id << " " << nl[i].parent << " " << nl[i].mincap << std::endl;
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


//depth first search routine
//~ void PadbergRao::dfs(int u){
    //~ visited[u] = true;
    //~ //std::vector<int>::iterator it;
    //~ components.back().push_back(u);
//~ 
    //~ for(auto it = adjacencyList[u].begin(); it != adjacencyList[u].end(); ++it ){
        //~ if( !visited[*it] ){
            //~ dfs(*it);
        //~ }
    //~ }
//~ }
//~ 
//~ //find minimum cut sets based on the results of DFS
//~ void PadbergRao::find_Component(){
   //~ for( int i = 0 ; i < numNodes; i++ ){
        //~ if(!visited[i]){ 
            //~ components.push_back(Component());
            //~ dfs(i);
        //~ }
    //~ } 
//~ }


void PadbergRao::remove_edge(){
	int i,origin,destination;
	
	for(i=1; i<numNodes; i++){
		//reconstruct graph, reset components and visited to inital status	    
		if(!components.empty()) components.clear();		
		for(int j=0; j<numNodes;j++){
			visited[j] = false;
		}

		//remove edge
		origin = nl[i].id;
		destination = nl[i].parent;  
        //print__gh_tree_adjacencyList();
		std::cout << "The removed edge is (" << origin << "," << destination << ")" << std::endl;
        
		adjacencyList[origin].erase(destination);
		adjacencyList[destination].erase(origin);	

		DFS::find_connected_components(numNodes, adjacencyList, visited, components);
        std::cout << "two components after remove this edge is " << std::endl;
		DFS::print_odd_component(components);

        // restore original adjacency list
		adjacencyList[origin].insert(destination);
        adjacencyList[destination].insert(origin);
	}
}



//~ void PadbergRao::print_Component(){
    //~ 
    //~ std::vector<Component>::iterator it1;    
    //~ std::vector<int>::iterator it2;
   //~ 
    //~ for (it1=components.begin();it1!=components.end();++it1){        
        //~ if((*it1).size() % 2 != 0){         
            //~ for(it2=it1->begin(); it2!=it1->end(); it2++) {
                //~ std::cout << *it2 << " ";
            //~ }
            //~ std::cout << std::endl;
        //~ }else{
            //~ std::cout << "no need to print !!!!!" << std::endl;
            //~ break;
        //~ }
//~ 
   	//~ }
//~ }

