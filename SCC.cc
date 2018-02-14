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

#include <math.h>
#include<vector>
#include<set>
#include<map>
#include<exception>
#include<algorithm>
#include<stdio.h>
#include<omp.h>
#include<iostream>

using namespace std;

void dfs1(int iV, vector<set<int> >& mapVecR, vector<bool>& visited, vector<int>& newOrder, int& times){
    visited[iV] =true;
    for(auto it=mapVecR[iV].begin(); it!=mapVecR[iV].end();it++){
	if(!visited[*it])
	    dfs1(*it, mapVecR, visited, newOrder, times);
    }
    newOrder[iV]=times;
    times++;	
}

int dfs2(int iV, vector<set<int> >& mapVec, vector<bool>& visited){
    visited[iV]=true;
    int num=1;
    for(auto it=mapVec[iV].begin(); it!=mapVec[iV].end();it++){
	if(!visited[*it])
	    num+=dfs2(*it, mapVec, visited);
    }
    return num;
}


int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/SCC.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/SSCtest2.txt", "r");
    char *line=NULL;
    size_t len;
    ssize_t read;
    vector< set<int> > mapVecR,mapVec;
    mapVec.resize(875750);
    mapVecR.resize(875750);
    int v1,v2,maxV;
    maxV=0;
    while ((read = getline(&line, &len, fd)) != -1) {
	sscanf(line, "%d %d", &v1,&v2);
	mapVecR[v2].insert(v1);
	mapVec[v1].insert(v2);
	maxV = max(max(v1,v2),maxV);
    }
    v1=maxV;
    vector<bool> visited;
    visited.resize(875750,false);
    vector<int> newOrder;
    newOrder.resize(875750,0);
    int times=1;
    for(int i=v1;i>0;i--)
	if(!visited[i])
	    dfs1(i,mapVecR,visited, newOrder,times);
    vector< set<int> > mapVec2;
    mapVec2.resize(875750);
    for(int i=1;i<=v1;i++){
	for(auto it=mapVec[i].begin();it!=mapVec[i].end();it++)
	    mapVec2[newOrder[i]].insert(newOrder[*it]);
    }
    vector<bool> visited2;
    visited2.resize(875750,false);
    multiset<int> SCCs;
    for(int i=v1;i>0;i--){
	if(!visited2[i])
	    SCCs.insert(dfs2(i, mapVec2, visited2));
    }
    
    auto iter=SCCs.rbegin(); 
    for(int i=0;i<std::min(15,(int)SCCs.size());i++,iter++)
	cout<<*iter<<" ";
    cout<<endl;
    return 0;
}

