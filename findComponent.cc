#include "findComponent.h"
#include <iostream>

findComponent::findComponent(double* lp_sol, int* edge_list, int num_edges, int num_vertices){
    this->num_vertices = num_vertices;
    this->num_edges = num_edges;
    totalComponents = 0;

    adjacencyList = new std::vector<int>[num_vertices];
    visited = new bool[num_vertices]();

    int origin,destination;
    for (int j = 0; j < num_edges; j++) {
        if (lp_sol[j] > LP_EPSILON) {
            origin = edge_list[2*j];
            destination = edge_list[2*j+1];
            adjacencyList[origin].push_back(destination);
            adjacencyList[destination].push_back(origin);
        }
    }
}


findComponent::~findComponent(){
	delete [] adjacencyList;
	delete [] visited; 
}

void findComponent::print_adjancencyList(){
    std::vector<int>::iterator it;
    for(int i=0; i<num_vertices; i++){             
        for(it = adjacencyList[i].begin(); it != adjacencyList[i].end(); ++it) {
            std::cout << (*it) << " " ;
        }
        std::cout << std::endl;
    }
}


void findComponent::dfs(int u){
    visited[u] = true;
    std::vector<int>::iterator it;
    components.back().push_back(u);

    for( it = adjacencyList[u].begin(); it != adjacencyList[u].end(); ++it ){
        if( !visited[*it] ){
            dfs( *it );
        }
    }
}


void findComponent::find_Component(){
   for( int i = 0 ; i < num_vertices; ++i ){
        if(!visited[i])
        { 
            components.push_back(Component());
            dfs(i);
            totalComponents++; ///increment number of components
        }
    } 
}

//no need to declare static again
void findComponent::print_Component(std::vector<Component> &c){
    
    std::vector<Component>::iterator it1;    
    std::vector<int>::iterator it2;

    for (it1=c.begin();it1!=c.end();++it1){
        for(it2=it1->begin(); it2!=it1->end(); it2++) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
        }
}


std::vector<Component> findComponent::componentList(){
    find_Component();
    return components;
}


bool findComponent::isConnected(){
	if(totalComponents==0){
		find_Component();
	}	
    if(totalComponents==1){
        return true;
    }else{
       //std::cout << "This graph is not connected, it has " << totalComponents << " components" <<std::endl;
       return false; 
    }
}

