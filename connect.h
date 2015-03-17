#ifndef __CONNECT__H
#define __CONNECT__H

#include "findComponent.h"
#include "subtour_util.h"


class connect
{
private:
	std::vector<IntPair> *adjacencyList;
	CO759lp *lp;
	std::vector<int> findDelta(Component &);	
	int add_subtour_util(std::vector<int>& );
public:
	connect(subtourUtil &);
	~connect();
	void add_subtours(std::vector<Component> &);
	
};

#endif
