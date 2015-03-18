
//#include "FordFulkerson.h"
#include "Graph.h"
#include "PadbergRao.h"

using namespace std;

int main()
{

	std::string filename = "undirected_graph";
	Graph g;
	g.read_input_file(filename);
	PadbergRao pr(g);
	//pr.print_gh_tree();
	cout << endl;
	// cout << endl;
	pr.remove_edge();
}
