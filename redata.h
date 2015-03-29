
//
//  Created by venicex on 15/3/21.
//  Copyright (c) 2015年 venicex. All rights reserved.
//

#define __redata__redata__

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
using namespace std;

void construct_b_graph(int ncount, int ecount, int* elist,int* elen,int* b, int & becount,int & bncount);

int incre_node(int ncount, int* b);

vector<int> split_node(int index, int ncount, int* b);

map<int,int> correspond_map(int ncount, int* b);