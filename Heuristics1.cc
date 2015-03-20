#include "Heuristics1.h"
#include <iostream>
#include <algorithm>
using namespace std;

Heuristics1::Heuristics1(RelaxedLP &rlp, Graph &g):adjacencyList(rlp.get_adjacencyList()),g(&g){
	lp = rlp.get_relaxed_lp();
}


std::vector<int> Heuristics1::findGamma(Component &c){	
	std::vector<int> gamma;
		
	for(auto it1=c.begin(); it1!=c.end(); it1++){
				
		for(auto it2=adjacencyList[*it1].begin(); it2!=adjacencyList[*it1].end();it2++){
			if(std::find(c.begin(), c.end(), (*it2).first)!=c.end()){
				gamma.push_back((*it2).second) ;
			}		
		}
    }
    return gamma;
}


/*
 *gamma is the set of index of the edges in delta(S), size = min(|S|,|V\S|) 
*/
int Heuristics1::add_constraint_util(std::vector<int>& gamma, int size)
{		
    int rval = 0, newrows = 1, newnz, *rmatind, gammacount;
    int rmatbeg[1];
    char sense[1];
    double rhs[1], *rmatval;
	
	gammacount = gamma.size();
	newnz = gammacount;
    rmatbeg[0] = 0; /* info for row starts at position 0 */
    
    rhs[0] = (size-1)/2.0 ;   /* right-hand-side of subtour is  (min(|S|,|V\S|)-1)/2*/
    sense[0] = 'L';    /* it is a <= inequality */
		
    rmatval = new double[gammacount];
    rmatind = new int[gammacount];
    for (int i = 0; i < gammacount; i++) {
		rmatval[i] = 1.0;
		rmatind[i] = gamma[i];
	}
    rval = CO759lp_addrows(lp, newrows, newnz, rhs, sense, rmatbeg,rmatind, rmatval);
    if (rval) {
        fprintf (stderr, "CO759lp_addrows failed: %d\n", rval);
        goto CLEANUP;
    }

CLEANUP:
    if (rmatval) delete [] rmatval;
    if (rmatind) delete [] rmatind;
    return rval;
}



void Heuristics1::add_constraint()
{
    /* Run through all component in components*/
    
	std::vector<Component> odd_cut_components = g->find_odd_cut_set();
	
	int n = g->get_num_nodes(),component_size;
    int rval=0;
    for(auto it=odd_cut_components.begin();it!=odd_cut_components.end();++it){
		component_size = (*it).size();	
		std::vector<int> gamma = findGamma(*it); 		
		rval = add_constraint_util(gamma,min(component_size,n-component_size));    
	    
	    if(rval){
	       fprintf(stderr, "add_constraint failed"); return;
	    }
	}
}

int Heuristics1::min(int x, int y){
	return x<y ? x : y;
}

Heuristics1::~Heuristics1(){}
