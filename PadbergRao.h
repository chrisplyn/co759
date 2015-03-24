#ifndef __PADBERGRAO_H__
#define __PADBERGRAO_H__

#include "GomoryHu.h"
#include "Heuristics1.h"
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
	void add_constraint_util(std::vector<Component>& , RelaxedLP&);

public:
	PadbergRao(Graph &);
	~PadbergRao();
	void add_constraint(RelaxedLP&);	
	void print_gh_tree();
	
};
#endif
