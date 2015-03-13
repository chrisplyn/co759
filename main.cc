
#include "FordFulkerson.h"


int main ()
{
	//int i,j;
	FordFulkerson ff;
	std::string filename = "mf.in";
	ff.read_input_file(filename);
	printf("total flow is %d\n",ff.max_flow(0,6-1));  // 0=source, n-1=sink

	// if (n<=20)
	// {
	//   printf("flows along edges:\n");
	//   for (i=0; i<residualEdges; i++)
	// 	if (edgeTab[i].flow>0)
	// 	  printf("%d->%d has %d\n",edgeTab[i].tail,
	// 		edgeTab[i].head,edgeTab[i].flow);
	// }
}