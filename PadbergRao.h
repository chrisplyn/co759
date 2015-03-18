#ifndef __PADBERGRAO_H__
#define __PADBERGRAO_H__

#include "GomoryHu.h"
#include <vector>
typedef std::vector<int> Component;



class PadbergRao
{
private:
	GomoryHu * const gh;
	const int numNodes;
	node *nl;
	std::vector<Component> components;
	std::vector<int> *adjacencyList;
	bool* visited;
	void dfs(int);
	void construct_gh_tree_adjacencyList();
	void find_Component();
	void print_Component();

public:
	PadbergRao(Graph &);
	~PadbergRao();
	void remove_edge();
	void print_gh_tree();
	void print__gh_tree_adjacencyList();
};
#endif