#include "Bimap.h"
#include <iostream>

int Bimap::add(int old_ind){	
	
	int i = forward.size();
	if(forward.find(old_ind) == forward.end()){		
		forward[old_ind] = i;
		backward[i] = old_ind;
	}	
	return forward[old_ind];	
}


int Bimap::get(int new_ind) const{
	return backward.at(new_ind);
}


int Bimap::get_size() const{
	return forward.size();
}

void Bimap::print_forward_map() const{
	for (auto iter = forward.begin(); iter != forward.end(); iter++){
		std::cout << "Key: " << iter->first << " " << "Values: " << iter->second << std::endl;
	}
}


void Bimap::print_backward_map() const{
	for (auto iter = backward.begin(); iter != backward.end(); iter++){
		std::cout << "Key: " << iter->first << " " << "Values: " << iter->second << std::endl;
	}
}
