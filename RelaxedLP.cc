#include "RelaxedLP.h"


RelaxedLP::RelaxedLP():numNodes(0),numEdges(0),edgeList(0),weightList(0),
					adjacencyList(0),obj_val(0.0),lp_sol(0),lp(0){}


RelaxedLP::~RelaxedLP(){
	destruct();
}


void RelaxedLP::destruct(){
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

	if(edgeList!=0){
      delete [] edgeList; 
    }

	if(weightList!=0) {
        delete [] weightList;
    }    
}



const std::vector<IntPair> * const RelaxedLP::get_adjacencyList(){
    if(adjacencyList!=0){
		return adjacencyList;
    }
       
    adjacencyList = new std::vector<IntPair>[numNodes];
    int origin,destination;
    
    for(int j=0; j<numEdges;j++){
        origin = edgeList[2*j];
        destination = edgeList[2*j+1];
		
		//keep track of index of each edge
        adjacencyList[origin].push_back(std::make_pair(destination, j));
        adjacencyList[destination].push_back(std::make_pair(origin, j));
    }
    return adjacencyList;
}



int RelaxedLP::euclid_edgelen (int i, int j, double *x, double *y)
{
    double t1 = x[i] - x[j], t2 = y[i] - y[j];
    return (int) (sqrt (t1 * t1 + t2 * t2) + 0.5);
}



int RelaxedLP::getprob(char *filename, int geometric_data, int seed, int ncount_rand, int gridsize_rand){
    FILE *f = (FILE *) NULL;
    int end1, end2, w, rval = 0;
	double *x=0, *y=0;
	
    if (filename) {
        if ((f = fopen (filename, "r")) == NULL) {
    	    fprintf (stderr, "Unable to open %s for input\n",filename);
            rval = 1;  goto CLEANUP;
        }
    }

    if (filename && geometric_data == 0) {
        if (fscanf (f, "%d %d", &numNodes, &numEdges) != 2) {
       	    fprintf (stderr, "Input file %s has invalid format\n",filename);
            rval = 1;  goto CLEANUP;
        }

        edgeList = new int[2*numEdges];
        if (!edgeList) {
            fprintf (stderr, "out of memory for elist\n");
            rval = 1;  goto CLEANUP;
        }

        weightList = new int[numEdges];
        if (!weightList) {
            fprintf (stderr, "out of memory for elen\n");
            rval = 1;  goto CLEANUP;
        }

        for (int i = 0; i < numEdges; i++) {
    	    if (fscanf(f,"%d %d %d",&end1, &end2, &w) != 3) {
	        fprintf (stderr, "%s has invalid input format\n", filename);
                rval = 1;  goto CLEANUP;
	    }

	    edgeList[2*i] = end1;
	    edgeList[2*i+1] = end2;
	    weightList[i] = w;
        }
    }else {
        if (filename) {
            if (fscanf (f, "%d", &numNodes) != 1) {
       	        fprintf (stderr, "Input file %s has invalid format\n",filename);
                rval = 1;  goto CLEANUP;
            }
        } else {
            numNodes = ncount_rand;
        }

        x = new double[numNodes];
        y = new double[numNodes];
        if (!x || !y) {
            fprintf (stdout, "out of memory for x or y\n");
            rval = 1; goto CLEANUP;
        }

        if (filename) {
            for (int i = 0; i < numNodes; i++) {
    	        if (fscanf(f,"%lf %lf",&x[i], &y[i]) != 2) {
	            fprintf (stderr, "%s has invalid input format\n", filename);
                    rval = 1;  goto CLEANUP;
	        }
            }
        } else {
            rval = CO759_build_xy (numNodes, x, y, gridsize_rand);
            if (rval) {
                fprintf (stderr, "CO759_build_xy failed\n");
                goto CLEANUP;
            }
    
            printf ("%d\n", numNodes);
            for (int i = 0; i < numNodes; i++) {
                printf ("%.0f %.0f\n", x[i], y[i]);
            }
            printf ("\n");
        }

        numEdges = (numNodes * (numNodes - 1)) / 2;
        printf ("Complete graph: %d nodes, %d edges\n", numNodes, numEdges);

		edgeList = new int[2*numEdges];
        if (!edgeList) {
            fprintf (stderr, "out of memory for edgeList\n");
            rval = 1;  goto CLEANUP;
        }

        weightList = new int[numEdges];
        if (!weightList) {
            fprintf (stderr, "out of memory for weightList\n");
            rval = 1;  goto CLEANUP;
        }

        int k = 0;
        for (int i = 0; i < numNodes; i++) {
            for (int j = i+1; j < numNodes; j++) {
                edgeList[2*k] = i;
                edgeList[2*k+1] = j;
                weightList[k] = euclid_edgelen (i, j, x, y);
                k++;
            }
        }
    } 
CLEANUP:
    if (f) fclose (f);
    if (x) delete [] x;
    if (y) delete [] y;
    return rval;    
}


/******************************
* initialize relaxed problem, adding all edges at once	
*******************************/
int RelaxedLP::init_relaxed_lp()
{
	if (edgeList == 0 || weightList == 0){
		fprintf (stderr, "must read problem from file first\n");
		exit(1);
	}

    int rval = 0, i, j;
    double  obj[1], lb[1];
    int     cmatbeg[1], cmatind[2];
    double  cmatval[2];

    lp = new CO759lp(); 

    rval = CO759lp_init (lp);
    if (rval) { fprintf (stderr, "CO759lp_init failed\n"); }

    rval = CO759lp_create(lp, "relaxed lp");
    if (rval) { fprintf (stderr, "CO759lp_create failed\n"); }

    for (i = 0; i < numNodes; i++) {
        rval = CO759lp_new_row (lp, 'E', 1.0);
        if (rval) {
            fprintf (stderr, "CO759lp_new_row failed\n"); 
        }
    }

    /* Build a column for each edge of the graph */
    cmatbeg[0] = 0;
    cmatval[0] = 1.0;
    cmatval[1] = 1.0;
    for (j = 0; j < numEdges; j++) {
        obj[0]     = (double) weightList[j];
        lb[0]      = 0.0;
        //ub[0]      = 1.0;
        cmatind[0] = edgeList[2*j];
        cmatind[1] = edgeList[2*j+1];
        rval = CO759lp_addcols(lp, 1 /* # of new variables */,
           2 /* # of new nonzeros */, obj, cmatbeg, cmatind, cmatval, lb, NULL);
        if (rval) {
            fprintf (stderr, "lp_addcols failed\n"); 
        }
    }
    return rval;
}

int RelaxedLP::get_num_edges(){
	return numEdges;
}

int RelaxedLP::get_num_nodes(){
	return numNodes;	
}

int const * RelaxedLP::get_edgeList(){
	return edgeList;	
}

double RelaxedLP::get_relaxed_lp_objval(){
    return obj_val;
}
    
double * RelaxedLP::get_relaxed_lp_sol(){
	if (lp_sol == 0) {
		destruct();
		printf("MUST CALL SOLVE_RELAXED_LP first!!!!!!!!");
		exit(3);
	}	
	return lp_sol;    
}    
    
 
CO759lp* RelaxedLP::get_relaxed_lp(){
    return lp;
}
    
    
int RelaxedLP::solve_relaxed_lp(){
    
    int infeasible;
    int rval = CO759lp_opt(lp, &infeasible);
    
    if (rval){
        fprintf(stderr, "CO759lp_opt failed\n"); 
    }
    if (infeasible){
        fprintf(stderr, "LP is infeasible\n"); 
        rval = 1; 
    }
	
	if(lp_sol==0){		
	   lp_sol = new double[numEdges]; //allocate memory for lp solution
	   if (!lp_sol){
            fprintf(stderr, "out of memory for lp_sol\n");
        	rval = 1; 
    	}
	}
    
    rval = CO759lp_write (lp, "matching.lp");
    if (rval) {
	   fprintf (stderr, "CO759lp_write failed\n"); 
    }
    
    rval = CO759lp_x(lp, lp_sol);
    if (rval) {
        fprintf(stderr, "CO759lp_x failed\n");
    }
    
    for (int j = 0; j < numEdges; j++) {
		if (lp_sol[j] > LP_EPSILON) 
         printf ("%d %d %f\n", edgeList[2*j], edgeList[2*j+1], lp_sol[j]); 
    }
    
    rval = CO759lp_objval(lp, &obj_val);
    if (rval) {
        fprintf (stderr, "CO759lp_objval failed\n"); 
    }
    
    return rval;
}


void RelaxedLP::print_relaxed_lp_sol(){
	if (lp_sol == 0) {
		destruct();
		printf("MUST CALL SOLVE_RELAXED_LP first!!!!!!!!");
		exit(4);
	}	
    
    for (int j = 0; j < numEdges; j++) {
		if (lp_sol[j] > LP_EPSILON) 
         printf ("%d %d %f\n", edgeList[2*j], edgeList[2*j+1], lp_sol[j]); 
    }
    fflush (stdout);
}
