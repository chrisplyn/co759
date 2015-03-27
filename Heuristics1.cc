#include "Heuristics1.h"
#include <iostream>
#include <algorithm>
using namespace std;


/*
* find set gamma of connected component c
*/
std::vector<int> Heuristics1::findGamma(Component &c, RelaxedLP &rlp){	
	const std::vector<IntPair> * const adjacencyList = rlp.get_adjacencyList();
	int edge_index;
	std::vector<int> gamma;		
	for(auto it1=c.begin(); it1!=c.end(); it1++){			
		for(auto it2=adjacencyList[*it1].begin(); it2!=adjacencyList[*it1].end();it2++){
			edge_index = (*it2).second;
			if(std::find(c.begin(), c.end(), (*it2).first)!=c.end() && 
			  std::find(gamma.begin(), gamma.end(), edge_index) == gamma.end()){
				gamma.push_back(edge_index) ;
			}		
		}
    }
    return gamma;
}


/*
 *gamma is the set of index of the edges in set gamma(S), size = min(|S|,|V\S|) 
*/
int Heuristics1::add_constraint_util(std::vector<int>& gamma, int size, RelaxedLP &rlp)
{		
	CO759lp *lp = rlp.get_relaxed_lp();
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



int Heuristics1::add_constraint(RelaxedLP &rlp, Graph& g, int &iter)
{
    /* Run through all component in components*/
    
	std::vector<Component> odd_cut_components = g.find_odd_cut_set();
		
	if(odd_cut_components.empty()){
	   //printf("no odd component has been found\n");
	   return 1;
	}
	
	double * lp_sol = rlp.get_relaxed_lp_sol();
	
    int rval=0;
    double sum;
    bool flag = false;
    for(auto it=odd_cut_components.begin();it!=odd_cut_components.end();++it){
		
		std::vector<int> gamma = findGamma(*it, rlp); 	
		sum = 0.0;
		for(auto it1=gamma.begin(); it1!=gamma.end();it1++){
			sum += lp_sol[*it1];	
		}
			
		if(sum > (double((*it).size())-1.0)/2.0+0.00001){				
			rval = add_constraint_util(gamma,(*it).size(),rlp);  
			flag = true;  
	    }
	    
	    if(rval){
	       fprintf(stderr, "add_constraint failed"); return 1;
	    }
	}
	
	iter++;
	if(flag){
		return 0;
	}else{		
		return 1;
	}
}







