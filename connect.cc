#include "connect.h"
#include <iostream>
#include <algorithm>
using namespace std;

connect::connect(subtourUtil &st){
	adjacencyList = st.get_adjacencyList();
	lp = st.get_subtour_lp();
}


std::vector<int> connect::findDelta(Component &c){
	std::vector<int>::iterator it1;
	std::vector<IntPair>::iterator it2;
	
	std::vector<int> delta;
	
	for(it1=c.begin(); it1!=c.end(); it1++){
		for(it2=adjacencyList[*it1].begin(); it2!=adjacencyList[*it1].end();it2++){
			if(std::find(c.begin(), c.end(), (*it2).first)==c.end()){
				delta.push_back((*it2).second) ;
			}		
		}
    }
    return delta;
}


int connect::add_subtour_util(std::vector<int>& delta)
{		
    int rval = 0, newrows = 1, newnz, *rmatind, deltacount;
    int rmatbeg[1];
    char sense[1];
    double rhs[1], *rmatval;
	
	deltacount = delta.size();
	newnz = deltacount;
    rmatbeg[0] = 0; /* info for row starts at position 0 */
    rhs[0] = 2.0;   /* right-hand-side of subtour is 2.0 */
    sense[0] = 'G';    /* it is a >= inequality */
		
    rmatval = new double[deltacount];
    rmatind = new int[deltacount];
    for (int i = 0; i < deltacount; i++) {
		rmatval[i] = 1.0;
		rmatind[i] = delta[i];
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



void connect::add_subtours(std::vector<Component>& components)
{
    /* Run through all component in components*/
   
    int rval=0;
    std::vector<Component>::iterator it;
    std::vector<int> delta;
    for(it=components.begin();it!=components.end();++it){	
		delta = findDelta(*it); 
		rval = add_subtour_util(delta);    
	    if(rval){
	       fprintf(stderr, "add_subtour failed"); return;
	    }
	}
}



connect::~connect(){}
