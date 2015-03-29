//
//  main.cpp
//
//  Created by venicex on 15/3/21.
//  Copyright (c) 2015年 venicex. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "redata.h"
#include <math.h>
#include <vector>
#include <map>
#include "util.h"
#include <stdlib.h>
using namespace std;


static void usage (char *f);
static int getprob (char *fname, char *fname2, int *p_ncount, int *p_ecount, int **p_elist,
                    int **p_elen,int **p_b);

int main(int argc, char * argv[]) {
    int rval  = 0, ncount = 0, ecount = 0,becount=0,bncount=0;
    map<int,int> indexmap;
    int *elist = (int *) NULL, *elen = (int *) NULL, *b = (int *) NULL;
    double szeit=CO759_zeit();
    rval = getprob (argv[1],argv[2], &ncount, &ecount, &elist, &elen, &b);
    if(argc<3){
        usage(argv[0]);
        goto CLEANUP;
    }
    if (argc==3){
        ofstream bgraph("b-graph.edg");
        construct_b_graph(ncount,ecount, elist,elen, b,becount,bncount);
        bgraph<<bncount<<" "<<becount<<endl;
        cout<<"b-graph has"<<becount<<"edges"<<endl;
        cout<<"b-graph has"<<bncount<<"nodes"<<endl;
        /*for(int i=0; i<becount;i++){
            cout<<elist[2*i]<<" "<<elist[2*i+1]<<" "<<elen[i] <<endl;
            bgraph<<elist[2*i]<<" "<<elist[2*i+1]<<" "<<elen[i]<<endl;
        }*/
        bgraph.close();
        cout<<"b-graph constructed successfuly in 'b-graph.edg'" <<endl;
        printf ("Running Time: %.2f seconds\n", CO759_zeit() - szeit);
        goto CLEANUP;
        
    }
    else if (argc==4){
        int *belist = (int *) NULL, *belen = (int *) NULL;
        rval=getprob (argv[3],argv[2], &bncount, &becount, &belist, &belen, &b);
        if (rval){
            goto CLEANUP
        }
        if (bncount!=2*becount) {
            cout<<"Input is not a matching"<<endl;
            free(belist);
            free(belen);
            goto CLEANUP;
        }
        indexmap=correspond_map(ncount,b);
        ofstream bmatching("b-matching.out");
        //cout<<indexmap.size()<<endl;
       // for(map<int,int>::iterator it=indexmap.begin();it!=indexmap.end();it++){
           // cout<<it->first<<" "<<it->second<<endl;
        //}
        for(int i=0; i<becount;i++){
            bmatching<<indexmap[belist[2*i]]<<" "<<indexmap[belist[2*i+1]]<<" "<<belen[i]<<endl;
        }
        bmatching.close();
        cout<<"1-matching in b-graph has successfuly converted into in 'b-matching.out'" <<endl;
        free(belist);
        free(belen);
        printf ("Running Time: %.2f seconds\n", CO759_zeit() - szeit);
        goto CLEANUP;
    }
    else{
        usage(argv[0]);
         printf ("Running Time: %.2f seconds\n", CO759_zeit() - szeit);
         goto CLEANUP;
    }
CLEANUP:
    if(elist) free(elist);
    if(elen) free(elen);
    if(b) free(b);
    return 0;
    
}



static void usage (char *f)
{
    fprintf (stderr, "Usage: %s [-see below-] [prob_file]\n", f);
    fprintf (stderr, "if we want to construct b-graph:'./redata [graph edge file] [b-vector]'\n");
    fprintf (stderr, "if we want to convert a matching in b-graph back to b-matching:'./redata [graph edge file] [b-vector][matching file] '\n");

}


static int getprob (char *fname, char *fname2, int *p_ncount, int *p_ecount, int **p_elist,
                    int **p_elen,int **p_b)
{
    FILE *f = (FILE *) NULL;
    FILE *f2 = (FILE *) NULL;
    int i, end1, end2, w, rval=0, bval = 0, ncount, ecount;
    int *elist = (int *) NULL, *elen = (int *) NULL, *b=(int*) NULL;
    
    if ((f = fopen (fname, "r")) == NULL) {
        fprintf (stderr, "Unable to open %s for input\n",fname);
        rval = 1;  goto CLEANUP;
    }
    
    if ((f2 = fopen (fname2, "r")) == NULL) {
        fprintf (stderr, "Unable to open %s for input\n",fname2);
        rval = 1;  goto CLEANUP;
    }
    
    if (fscanf (f, "%d %d", &ncount, &ecount) != 2) {
        fprintf (stderr, "Input file %s has invalid format\n",fname);
        rval = 1;  goto CLEANUP;
    }
    
    printf ("Nodes: %d  Edges: %d\n", ncount, ecount);
    fflush (stdout);
    
    b=(int *) malloc (ncount * sizeof (int));
    elist = (int *) malloc (2 * ecount *ecount* sizeof (int));
    if (!elist) {
        fprintf (stderr, "out of memory for elist\n");
        rval = 1;  goto CLEANUP;
    }
    
    elen = (int *) malloc (ecount*ecount * sizeof (int));
    if (!elen) {
        fprintf (stderr, "out of memory for elen\n");
        rval = 1;  goto CLEANUP;
    }
    for (i = 0; i < ncount; i++) {
        if (fscanf(f2,"%d=",&bval) != 1) {
            fprintf (stderr, "%s has invalid input format\n",fname);
            rval = 1;  goto CLEANUP;
        }
        b[i]=bval;
    }

    for (i = 0; i < ecount; i++) {
        if (fscanf(f,"%d %d %d",&end1, &end2, &w) != 3) {
            fprintf (stderr, "%s has invalid input format\n",fname);
            rval = 1;  goto CLEANUP;
        }
        elist[2*i] = end1;
        elist[2*i+1] = end2;
        elen[i] = w;
    }
    
    *p_ncount = ncount;
    *p_ecount = ecount;
    *p_elist = elist;
    *p_elen = elen;
    *p_b=b;
    
CLEANUP:
    if (f2) fclose (f2);
    if (f) fclose (f);
    return rval;
}



