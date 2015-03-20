#ifndef __PADBERGRAO_H__
#define __PADBERGRAO_H__

#include "GomoryHu.h"
#include <vector>
#include <unordered_set>

typedef std::vector<int> Component;
typedef std::unordered_set<int> set;


class PadbergRao
{
private:
	GomoryHu * const gh;
	const int numNodes;
	node *nl;
	set *adjacencyList;
	bool* visited;
	std::vector<Component> components;
	//void dfs(int);
	void construct_gh_tree_adjacencyList();
	//void find_Component();
	//void print_Component();

public:
	PadbergRao(Graph &);
	~PadbergRao();
	void remove_edge();
	void print_gh_tree();
	//void print__gh_tree_adjacencyList();
};
#endif
