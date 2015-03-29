#ifndef __BIMAP_H__
#define __BIMAP_H__

#include <unordered_map>

typedef std::unordered_map<int,int> intmap;

class Bimap{
	intmap forward, backward;	//forward map: new_ind->old_ind; backward map: old_ind->new_ind

public:
	int add(int old_ind);	
	int get(int new_ind) const;	//return old_ind
	int get_size() const;
	void print_forward_map() const;
	void print_backward_map() const;
};

#endif	
