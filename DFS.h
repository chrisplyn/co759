#ifndef __DFS_H__
#define __DFS_H__

/****************************************************************************/
/*                                                                          */
/*              Utility function for Depth First Search           			*/
/*                                                  						*/
/*                                                                          */
/****************************************************************************/

#include <vector>
#include <unordered_set>
typedef std::vector<int> Component;
typedef std::unordered_set<int> set;

class DFS
{
private:
	static void dfs(int, const set *, bool *, std::vector<Component>& );		
	
public:
	static void find_connected_components(int, const set *, bool *, std::vector<Component>& );
	static void print_adjacencyList(int , const set *);
	static void print_odd_component(const std::vector<Component> &);
};


#endif
