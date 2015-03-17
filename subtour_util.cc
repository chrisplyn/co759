#include "subtour_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "util.h"

//~ int subtourUtil::geometric_data = 0;
//~ int subtourUtil::seed = 0;
//~ int subtourUtil::ncount_rand = 0;
//~ int subtourUtil::gridsize_rand = 100;

/*
constructor of subtour_util
*/
subtourUtil::subtourUtil():num_vertices(0),num_edges(0),weight_list(0),edge_list(0),lp(0),obj_val(0){
    adjacencyList = 0;
    lp_sol = 0;
}

subtourUtil::~subtourUtil(){
	destruct();
}

void subtourUtil::set_lp_sol(double* lp_sol){
	this->lp_sol = lp_sol;	
}

void subtourUtil::destruct(){
    if(lp_sol!=0){
        delete [] lp_sol;
    }
    
    if (lp!=0){
        CO759lp_free(lp);
        delete lp;
    }

    if(adjacencyList != 0){
        delete [] adjacencyList;
    }

}


// int* subtourUtil::get_edge_list(){
//     return edge_list;
// }

// int* subtourUtil::get_weight_list(){
//     return weight_list;
// }


CO759lp* subtourUtil::get_subtour_lp(){
    return lp;
}
    

// std::vector<IntPair> *subtourUtil::get_weighted_adjacencyList(){
//     if(weighted_adjacencyList!=0){
// 		return weighted_adjacencyList;
//     }    
//     weighted_adjacencyList = new std::vector<IntPair>[num_vertices];
//     int origin,destination,weight;
//     for(int j=0; j<num_edges;j++){
//         origin = edge_list[2*j];
//         destination = edge_list[2*j+1];
//         weight = weight_list[j];

//         weighted_adjacencyList[origin].push_back(std::make_pair(destination, weight));
//         weighted_adjacencyList[destination].push_back(std::make_pair(origin, weight));
//     }
//     return weighted_adjacencyList;
// }


std::vector<IntPair> *subtourUtil::get_adjacencyList(){
    if(adjacencyList!=0){
		return adjacencyList;
    }
        
    adjacencyList = new std::vector<IntPair>[num_vertices];
    int origin,destination;
    for(int j=0; j<num_edges;j++){
        origin = edge_list[2*j];
        destination = edge_list[2*j+1];
		
		//keep track of index of each edge
        adjacencyList[origin].push_back(std::make_pair(destination, j));
        adjacencyList[destination].push_back(std::make_pair(origin, j));
    }
    return adjacencyList;
}


double subtourUtil::get_subtour_lp_objval(){
    return obj_val;
}
    
    
double* subtourUtil::get_subtour_lp_sol(){
    
    int infeasible;
    int rval = CO759lp_opt(lp, &infeasible);
    
    if (rval){
        fprintf(stderr, "CO759lp_opt failed\n"); 
    }
    if (infeasible){
        fprintf(stderr, "LP is infeasible\n"); 
        rval = 1; 
    }
	
	//~ if(lp_sol==0){		
		//~ lp_sol = new double[num_edges]; //allocate memory for lp solution
	//~ }
    //~ 
    rval = CO759lp_write (lp, "subtour.lp");
    if (rval) {
	   fprintf (stderr, "CO759lp_write failed\n"); 
    }
    
    if (!lp_sol){
        fprintf(stderr, "out of memory for lp_sol\n");
        rval = 1; 
    }
    
    rval = CO759lp_x(lp, lp_sol);
    if (rval) {
        fprintf(stderr, "CO759lp_x failed\n");
    }
    
    rval = CO759lp_objval(lp, &obj_val);
    if (rval) {
        fprintf (stderr, "CO759lp_objval failed\n"); 
    }    
    return lp_sol;
}


void subtourUtil::print_subtour_lp_objval(){
    printf ("Degree-Equation LP Value: %f\n", obj_val);
    fflush (stdout);
}


void subtourUtil::print_subtour_lp_sol(){
    int i=0,j;
    for (j = 0; j < num_edges; j++) {
        if (lp_sol[j] > LP_EPSILON) i++;
    }

    printf ("LP graph has %d edges\n", i);
    for (j = 0; j < num_edges; j++) {
        if (lp_sol[j] > LP_EPSILON) {
            printf ("%d %d %f\n", edge_list[2*j], edge_list[2*j+1], lp_sol[j]);
        }
    }
    fflush (stdout);
}


int subtourUtil::init_subtour_prob()
{
    int rval = 0, i, j;
    double  obj[1], lb[1], ub[1];
    int     cmatbeg[1], cmatind[2];
    double  cmatval[2];

    lp = new CO759lp();
    rval = CO759lp_init (lp);
    if (rval) { fprintf (stderr, "CO759lp_init failed\n"); }

    rval = CO759lp_create(lp, "subtour");
    if (rval) { fprintf (stderr, "CO759lp_create failed\n"); }

    for (i = 0; i < num_vertices; i++) {
        rval = CO759lp_new_row (lp, 'E', 2.0);
        if (rval) {
            fprintf (stderr, "CO759lp_new_row failed\n"); 
        }
    }

    /* Build a column for each edge of the graph */
    cmatbeg[0] = 0;
    cmatval[0] = 1.0;
    cmatval[1] = 1.0;
    for (j = 0; j < num_edges; j++) {
        obj[0]     = (double) weight_list[j];
        lb[0]      = 0.0;
        ub[0]      = 1.0;
        cmatind[0] = edge_list[2*j];
        cmatind[1] = edge_list[2*j+1];
        rval = CO759lp_addcols(lp, 1 /* # of new variables */,
           2 /* # of new nonzeros */, obj, cmatbeg, cmatind, cmatval, lb, ub);
        if (rval) {
            fprintf (stderr, "CClp_addcols failed\n"); 
        }
    }
    return rval;
}
