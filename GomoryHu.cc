#include "GomoryHu.h"
#include <iostream>

GomoryHu::GomoryHu(const Graph& g):numNodes(g.get_num_nodes()),gr(&g){
	nodeList = 0;
}

GomoryHu::~GomoryHu(){}

node * GomoryHu::construct_GH_tree(){
	FordFulkerson ff(*gr);
	
	//printf("total flow is %d\n",ff.max_flow(0,5));  // 0=source, n-1=sink
	//nodeList = ff.get_nodeList();


	// for(int i=0; i<numNodes; i++){
	// 	if(nodeList[i].s_side){
	// 		std::cout << nodeList[i].id << " is on S side of min-cut" << std::endl;
	// 	}else{
	// 		std::cout << nodeList[i].id << " is on T side of min-cut" << std::endl;
	// 	}
	// }
   nodeList = ff.get_nodeList();
   
   int maxfl,i,s,t;
   
   for(i=0;i<numNodes;i++){
   	   nodeList[i].parent = &(nodeList[0]);
   }

   // for(s=0;s<numNodes;s++){
   // 		for(t=0;t<numNodes;t++){
   // 			if(s!=t)  maxfl = ff.max_flow(s,t);
   // 		}
   // }

   for ( s=1; s<numNodes; s++ )
   { 
      t = nodeList[s].parent->id;
      maxfl = ff.max_flow(s,t);

      //maxfl < 0 <=> graph is not connected => generate cut
      // if ( maxfl < 0L )
      // {
      //    constructSingleCut(gr,cuts);
      //    *ncuts = 1;
      //    return TRUE;
      // }
           
      nodeList[s].mincap = maxfl;

      for ( i=0; i<numNodes; i++ ){
        if ( i!=s && nodeList[i].s_side && nodeList[i].parent->id == t ){
            nodeList[i].parent = &(nodeList[s]);
        }    
      }

      if ( nodeList[t].parent->s_side )
      { 
         nodeList[s].parent = nodeList[t].parent;
         nodeList[t].parent = &(nodeList[s]);
         nodeList[s].mincap = nodeList[t].mincap;
         nodeList[t].mincap = maxfl;
      }
   }
   return nodeList;
}