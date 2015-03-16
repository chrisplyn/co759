#ifndef __GOMORYHU_H__
#define __GOMORYHU_H__

#include "FordFulkerson.h"


class GomoryHu
{
private:
	node * nodeList;
	const int numNodes;
	Graph const * const gr;

public:
	GomoryHu(const Graph&);
	~GomoryHu();
	node * construct_GH_tree();
	/* data */
};

#endif