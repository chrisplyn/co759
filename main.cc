
#include "Graph.h"
#include "util.h"
#include "PadbergRao.h"
#include "RelaxedLP.h"
#include <getopt.h>
#include "Heuristics1.h"
#include <math.h>
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
    srandom (seed);

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
	
	int ind=0, ind2=0;
	
	double tmp, objval=0.0, szeit = CO759_zeit ();
	
	while(true){
		rval = rlp.solve_relaxed_lp();
		
		tmp = objval;
		objval = rlp.get_relaxed_lp_objval();
						
		Graph g_star(rlp);			
		if(g_star.check_integrality()) break; 
		
		if(ind <= 10) {					
			if(abs(objval-tmp)/tmp < 0.01){
				ind++;
			}else{
				ind=0;
			}

			g_star.construct_g_star();
			rval = Heuristics1::add_constraint(rlp,g_star);				
		}
		
		if(rval || ind > 10){
			
			if( ind2 <= 10){
				if(abs(objval-tmp)/tmp < 0.01){
					ind2++;
				}else{
					ind2=0;
				}

				g_star.construct_g_star_2();			
				rval = Heuristics1::add_constraint(rlp,g_star);
			}
		}	
			
		if(rval || (ind>10 && ind2>10)){

			 g_star.construct_g_star();
			 g_star.construct_g_star_prime();
			 PadbergRao pr(g_star);
			 pr.add_constraint(rlp);	
		}
		
	}	
	cout << "the length of optimal matching is " <<  rlp.get_relaxed_lp_objval() << endl;
	cout <<  "running time of the perfect 1-matching program is " << CO759_zeit() - szeit << endl;
	rlp.write_relaxed_lp_sol("matching.out");
}
