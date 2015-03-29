
//
//  Created by venicex on 15/3/21.
//  Copyright (c) venicex. All rights reserved.
//
#ifndef __redata__redata__
#define __redata__redata__

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>

void construct_b_graph(int ncount, int ecount, int* elist,int* elen,int* b, int & becount,int & bncount);

int incre_node(int ncount, int* b);

std::vector<int> split_node(int index, int ncount, int* b);

std::map<int,int> correspond_map(int ncount, int* b);

#endif
