//
//  autodata.h
//  autodata
//
//  Created by venicex on 15/3/21.
//  Copyright (c) 2015年 venicex. All rights reserved.
//

#define __autodata__autodata__

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
using namespace std;

map<int,int> auto_data(int ncount, int ecount, int* elist,int* b, int & becount,int & bncount);

int incre_node(int ncount, int* b);

vector<int> split_node(int index, int ncount, int* b);

