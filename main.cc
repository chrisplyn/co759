
//#include "FordFulkerson.h"
#include "Graph.h"
#include "GomoryHu.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main()
{

	std::string filename = "undirected_graph";
	Graph g;
	g.read_input_file(filename);
	GomoryHu gh(g);
	node* nl = gh.construct_GH_tree();
	const int numNodes = g.get_num_nodes();
	
	
	sort(nl,nl+numNodes); //c++ type of sorting


	for(int i=0; i<numNodes; i++){
		// if(nl[i].s_side){
		// 	cout << nl[i].id << " is on S side of min-cut" << endl;
		// }else{
		// 	cout << nl[i].id << " is on T side of min-cut" << endl;
		// }
		//printf("%d %d %5f\n",nl[i].id, nl[i].parent->id, nl[i].mincap);
		//cout << nl[i].id << endl;
		
		cout << nl[i].id << " " << nl[i].parent->id << " " << setprecision(7) << nl[i].mincap << endl;
	}

	// for(int i=0; i<numEdges; i++){
	// 	cout << elist[2*i] << " " << elist[2*i+1] << endl;
	// }

}
