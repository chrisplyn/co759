
#include "FordFulkerson.h"
#include "Graph.h"
#include <iostream>
using namespace std;

int main ()
{
	//int i,j;
	//FordFulkerson ff;
	std::string filename = "mf.in";
	Graph g;
	g.read_input_file(filename);
	FordFulkerson ff(g);
	//ff.construct_residual_graph();
	printf("total flow is %d\n",ff.max_flow(1,3));  // 0=source, n-1=sink

	// int numEdges = g.get_num_edges();
	// int	const * const elist = g.get_edgeList();	//a constant pointer to a constant object

	// for(int i=0; i<numEdges; i++){
	// 	cout << elist[2*i] << " " << elist[2*i+1] << endl;
	// }


	//printf("total flow is %d\n",ff.max_flow(0,6-1));  // 0=source, n-1=sink

	// if (n<=20)
	// {
	//   printf("flows along edges:\n");
	//   for (i=0; i<residualEdges; i++)
	// 	if (edgeTab[i].flow>0)
	// 	  printf("%d->%d has %d\n",edgeTab[i].tail,
	// 		edgeTab[i].head,edgeTab[i].flow);
	// }
}