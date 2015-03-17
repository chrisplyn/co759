#ifndef __FIND_COMPONENT__H
#define __FIND_COMPONENT__H


#include <vector>
#define LP_EPSILON 0.000001
typedef std::vector<int> Component;

class findComponent
{
private:
	int num_vertices, num_edges, totalComponents;
	std::vector<Component> components;
	std::vector<int> *adjacencyList;
	bool* visited;
	void dfs(int);
	void find_Component();
public:
	findComponent(double*, int*, int, int);
	~findComponent();
	void print_adjancencyList();
	static void print_Component(std::vector<Component> &);
	std::vector<Component> componentList();
	bool isConnected();

};

#endif
