#ifndef __SUBTOURUTIL_H__
#define __SUBTOURUTIL_H__


#include "lp.h"
#include <vector>
#include <utility> 
#define LP_EPSILON 0.000001
typedef std::pair<int,int> IntPair;

class subtourUtil{

private:
	std::vector<IntPair> *adjacencyList;
	double obj_val,*lp_sol;
	CO759lp *lp;
	void destruct();
public:
	subtourUtil();
	~subtourUtil();
	int init_subtour_prob();
	CO759lp *get_subtour_lp();	
	double get_subtour_lp_objval();
	double *get_subtour_lp_sol();
	void print_subtour_lp_objval();
	void print_subtour_lp_sol();

	std::vector<IntPair> *get_adjacencyList();
	void set_lp_sol(double *);
};

#endif
