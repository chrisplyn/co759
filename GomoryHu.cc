#include "GomoryHu.h"
#include <iostream>

GomoryHu::GomoryHu(const Graph& g):numNodes(g.get_num_nodes()),ff(new FordFulkerson(g)){
}

GomoryHu::~GomoryHu(){
	delete ff;
}

node * GomoryHu::construct_GH_tree(){

   node * nodeList = ff->get_nodeList();
   
   int i,s,t;
   double maxfl;
   for(i=0;i<numNodes;i++){
   	nodeList[i].parent = &(nodeList[0]);
   }

   for ( s=1; s<numNodes; s++){ 

      t = nodeList[s].parent->id;
      maxfl = ff->max_flow(s,t);
           
      nodeList[s].mincap = maxfl;

      for ( i=0; i<numNodes; i++ ){
        if ( i!=s && nodeList[i].s_side && nodeList[i].parent->id == t ){
            nodeList[i].parent = &(nodeList[s]);
        }    
      }

      if ( nodeList[t].parent->s_side ){ 
         nodeList[s].parent = nodeList[t].parent;
         nodeList[t].parent = &(nodeList[s]);
         nodeList[s].mincap = nodeList[t].mincap;
         nodeList[t].mincap = maxfl;
      }
   }
   return nodeList;
}
