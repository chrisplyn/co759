#ifndef __GOMORYHU_H__
#define __GOMORYHU_H__

#include "FordFulkerson.h"


class GomoryHu
{
private:
	const int numNodes;
	FordFulkerson * const ff;

public:
	GomoryHu(const Graph&);
	~GomoryHu();
	node * construct_GH_tree();
};

#endif
