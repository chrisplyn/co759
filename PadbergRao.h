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
	const Bimap &g_prime_node_map;
	
	void construct_gh_tree_adjacencyList();
	void add_constraint_util(std::vector<Component>& , RelaxedLP&);

public:
	PadbergRao(Graph &);
	~PadbergRao();
	void add_constraint(RelaxedLP&);	
	void print_gh_tree();
	
};
#endif
