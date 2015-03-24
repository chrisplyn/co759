
#include "Graph.h"
#include "PadbergRao.h"
#include "RelaxedLP.h"
#include <getopt.h>
#include "Heuristics1.h"
using namespace std;

static char *fname = (char *) NULL;
static int seed = 0;
static int geometric_data = 0;
static int ncount_rand = 0;
static int gridsize_rand = 100;


static void usage (char *f)
{
    fprintf (stderr, "Usage: %s [-see below-] [prob_file]\n", f);
    fprintf (stderr, "   -b d  gridsize d for random problems\n");
    fprintf (stderr, "   -g    prob_file has x-y coordinates\n");
    fprintf (stderr, "   -k d  generate problem with d cities\n");
    fprintf (stderr, "   -s d  random seed\n");
}


static int parseargs (int ac, char **av)
{
    int c;

    if (ac == 1) {
        usage (av[0]);
        return 1;
    }

    while ((c = getopt (ac, av, "b:gk:s:")) != EOF) {
        switch (c) {
        case 'b':
            gridsize_rand = atoi (optarg); 
            break;
        case 'g':
            geometric_data = 1;
            break;
        case 'k':
            ncount_rand = atoi (optarg);
            break;
        case 's':
            seed = atoi (optarg);
            break;
        case '?':
        default:
            usage (av[0]);
            return 1;
        }
    }
    if (optind < ac) fname = av[optind++];
    if (optind != ac) {
        usage (av[0]);
        return 1;
    }

    return 0;
}



int main(int ac, char **av)
{
	int rval;
	
	seed = (int) CO759_real_zeit ();
	rval = parseargs (ac, av);
    if (rval) return 0;

    if (!fname && !ncount_rand) {
        printf ("Must specify a problem file or use -k for random prob\n");
        rval = 1; return 0; 
    }
    printf ("Seed = %d\n", seed);
    srandom (seed);

    if (fname) {
        printf ("Problem name: %s\n", fname);
        if (geometric_data) printf ("Geometric data\n");
    }
	
	RelaxedLP rlp;
    rval = rlp.getprob(fname, geometric_data, seed, ncount_rand, gridsize_rand);
    if (rval) {
        fprintf (stderr, "getprob failed\n");
        return 0;
    }	
	
	rval = rlp.init_relaxed_lp();
	if(rval){
		cout << "initializing subtour problem failed" << endl;
		return 0;
	}
	
	int i = 0;
	while(i<100){
		i++;
		rval = rlp.solve_relaxed_lp();		
		Graph g_star(rlp);
		g_star.construct_g_star();		
		if(g_star.check_integrality()) break; 
		Heuristics1::add_constraint(rlp,g_star);		
	}	
	cout << "final lp solution is"  << endl;
	rlp.print_relaxed_lp_sol();
	cout << "number of iterations is " << i << endl;
	

	
	
	//~ int i = 0;
	//~ while(true){
		//~ i++;
		//~ rval = rlp.solve_relaxed_lp();		
		//~ Graph g_star(rlp);		
		//~ g_star.construct_g_star();
		//~ if(g_star.check_integrality()) break; 
		//~ g_star.convert_g_star();		
		//~ PadbergRao pr(g_star);
		//~ pr.add_constraint(rlp);			
	//~ }	
	//~ cout << "final lp solution is"  << endl;
	//~ rlp.print_relaxed_lp_sol();
	//~ cout << "number of iterations is " << i << endl;
	
	
	

}
