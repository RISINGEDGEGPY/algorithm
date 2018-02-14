/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pengyuan
 *
 * Created on November 6, 2017, 9:20 PM
 */

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <string>
#include <string.h>
#include<stdlib.h>
#include<vector>
#include<set>
#include<map>
#include<exception>
#include<algorithm>
#include<fstream>
#include<stdio.h>
#include<omp.h>
using namespace std;

int cutGraph(map<int,multiset<int>> graphMap, int n2Edge){
    int minCut=numeric_limits<int>::max();
    while(graphMap.size()>2){
	int redEdge= 1+((double)rand())/(RAND_MAX+1.0) * n2Edge;
	auto iter = graphMap.begin();
	while(1){
	    if((iter->second).size()<redEdge){
		redEdge=redEdge - (iter->second).size();
		iter++;
	    }else{
		break;
	    }
	}
	auto iterSet = (iter->second).begin();
	for(int i=1;i<redEdge;i++)
	    iterSet++;
	auto iter2 = graphMap.find(*iterSet);
	for(auto it=(iter2->second).begin();it!=(iter2->second).end();it++){
	    if(*it!= iter->first){
		auto refV = graphMap.find(*it);
		auto itV = (refV->second).find(iter2->first);
		(refV->second).insert(iter->first);
		(refV->second).erase(itV);
	    }
	}
	(iter->second).insert((iter2->second).begin(),(iter2->second).end());
	n2Edge=n2Edge - (iter->second).count(iter->first)-(iter->second).count(iter2->first);
	(iter->second).erase(iter->first);
	(iter->second).erase(iter2->first);
	graphMap.erase(iter2);
    }
    return (graphMap.begin()->second).size();
}

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/MinCut.txt", "r");
    char tmpInt[1024];
    char delem[]=" \t";
    map<int, multiset<int>> graphMap;
    int n2Edge=0;
    while(fgets(tmpInt, 1024, fd)){
	char* iter=tmpInt;
	multiset<int> tmpVSet;
	char* tok;
	tok=strtok(tmpInt, delem);
	int tmpVertice = atoi(tok);
	while((tok=strtok(NULL, delem))!=NULL ){
	    if(atoi(tok)==0)
		continue;
	    tmpVSet.insert(atoi(tok));
	    n2Edge++;
	}
	graphMap.insert(pair<int,multiset<int>>(tmpVertice, tmpVSet));
    }
    //begin random algorithm
    int nV = graphMap.size();
    int minCut=numeric_limits<int>::max();
//#pragma omp parallel for
    for(int i=0;i<nV*nV*(log2(nV)+1);i++){
	minCut = min(minCut, cutGraph(graphMap, n2Edge));
	if(i%100==0)
	    cout<<minCut<<endl;
    }

    return 0;
}


