#include "DFS.h"
#include <iostream>
	
void DFS::dfs(int u, const set *adjacencyList, bool *visited, std::vector<Component> &components){
    visited[u] = true;
    components.back().push_back(u);
	
    for(auto it = adjacencyList[u].begin(); it != adjacencyList[u].end(); ++it ){
        if( !visited[*it] ){
            dfs(*it, adjacencyList, visited, components);
        }
    }
}

void DFS::find_connected_components(int numNodes, const set *adjacencyList, 
			bool *visited, std::vector<Component> &components){
   for( int i = 0 ; i < numNodes; i++ ){
        if(!visited[i]){ 
            components.push_back(Component());
            dfs(i,adjacencyList,visited,components);
        }
    } 
}


void DFS::print_adjacencyList(int numNodes, const set *adjacencyList){
	 
    for(int i=0; i<numNodes; i++){   
		std::cout << "the neighbor of " << i << " is " ;          
        for(auto it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it) {
            std::cout << (*it) << " " ;
        }
        std::cout << std::endl;
    }
}


void DFS::print_odd_component(const std::vector<Component> &components){
    if(components.empty()){
	  std::cout << "components cannot be empty!!!!!!!!!!" << std::endl;
	  return;
    } 
    
    std::cout << "number of component is " << components.size() << std::endl;
    for (auto it1=components.begin();it1!=components.end();++it1){		              
        for(auto it2=it1->begin(); it2!=it1->end(); it2++){
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;  
   	}
}


void DFS::print_component(const Component &c){
    if(c.empty()){
	  std::cout << "c cannot be empty!!!!!!!!!!" << std::endl;
	  return;
    } 
                
    for(auto it=c.begin(); it!=c.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;    	
}



