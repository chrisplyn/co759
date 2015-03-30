
//
//  Created by venicex on 15/3/21.
//  Copyright (c) 2015 venicex. All rights reserved.
//

#include "redata.h"
using namespace std;


void construct_b_graph(int ncount, int ecount, int* elist,int* elen,int* b, int & becount,int & bncount){
    vector<vector<int>> edgevector;
    vector<int> x;
    map<int,int> indexmap;
    int newecount=ecount-1;
    bncount=ncount+incre_node(ncount,b);
    
    for (int i=0;i<ncount;i++){
        indexmap[i]=i;
        x=split_node(i,ncount,b);
        edgevector.push_back(x);
        if (!x.empty()){
            for (vector<int>::iterator it=x.begin(); it!=x.end();it++){
                indexmap[*it]=i;
                }
        }
    }
    for (int i=0;i<ecount;i++){
        if (!edgevector[elist[2*i]].empty() && !edgevector[elist[2*i+1]].empty()){
            for (vector<int>::iterator it=edgevector[elist[2*i]].begin();it!=edgevector[elist[2*i]].end();it++){
                newecount++;
                elen[newecount]=elen[i];
                elist[2*newecount]=*it;
                elist[2*newecount+1]=elist[2*i+1];
            }
            for (vector<int>::iterator it2=edgevector[elist[2*i+1]].begin();it2!=edgevector[elist[2*i+1]].end();it2++){
                newecount++;
                elen[newecount]=elen[i];
                elist[2*newecount]=elist[2*i];
                elist[2*newecount+1]=*it2;
            }
            for (vector<int>::iterator it=edgevector[elist[2*i]].begin();it!=edgevector[elist[2*i]].end();it++){
                for (vector<int>::iterator it2=edgevector[elist[2*i+1]].begin();it2!=edgevector[elist[2*i+1]].end();it2++){
                    newecount++;
                    elen[newecount]=elen[i];
                    elist[2*newecount]=*it;
                    elist[2*newecount+1]=*it2;
                }
            }
        }
        if (edgevector[elist[2*i]].empty() && !edgevector[elist[2*i+1]].empty()){
            for (vector<int>::iterator it2=edgevector[elist[2*i+1]].begin();it2!=edgevector[elist[2*i+1]].end();it2++){
                newecount++;
                elen[newecount]=elen[i];
                elist[2*newecount]=elist[2*i];
                elist[2*newecount+1]=*it2;
            }
        }
        if (!edgevector[elist[2*i]].empty() && edgevector[elist[2*i+1]].empty()){
            for (vector<int>::iterator it=edgevector[elist[2*i]].begin();it!=edgevector[elist[2*i]].end();it++){
                newecount++;
                elen[newecount]=elen[i];
                elist[2*newecount]=*it;
                elist[2*newecount+1]=elist[2*i+1];
            }
        }
        if (edgevector[elist[2*i]].empty() && edgevector[elist[2*i+1]].empty()){
            continue;
        }
        
    }
    becount=newecount+1;
    
}


vector<int> split_node(int index, int ncount, int* b){
    vector<int> spldnode;
    if(b[index]==1){
        return spldnode;
    }

    for (int i=0; i<b[index]-1;i++){
            spldnode.push_back(ncount+incre_node(index,b)+i);
    }

        return spldnode;
    
}

int incre_node(int ncount, int* b){
    int incr_ncount=0;
    for(int i=0;i<ncount;i++){
        incr_ncount+=b[i]-1;
    }
    return incr_ncount;
    
}


map<int,int> correspond_map(int ncount, int* b){
    vector<vector<int>> edgevector;
    vector<int> x;
    map<int,int> indexmap;
    //cout<<"G hsa:"<<ncount<<endl;
    for (int i=0;i<ncount;i++){
        indexmap[i]=i;
        x=split_node(i,ncount,b);
        edgevector.push_back(x);
        if (!x.empty()){
            for (vector<int>::iterator it=x.begin(); it!=x.end();it++){
                indexmap[*it]=i;
            }
        }
    }
    return indexmap;
}
