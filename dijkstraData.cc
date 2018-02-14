#include <iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;
int A[201];
//struct heapComp{
//    bool operator()(const int& a, const int& b) const{
//	if(A[a]>A[b])
//	    return true;
//	else return false;
//    }
//};
struct greater1{	    
    bool operator()(const int& a,const int& b) const{	       
	return A[a]>A[b];
	//return a>b;
    }
};	
struct less1{	    
    bool operator()(const int& a,const int& b) const{	       
	return A[a]<A[b];
	//return a>b;
    }
};	

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/dijkstraData.txt", "r");
    char tmpInt[1024];
    char delem[]=" \t";
    for(int i=0;i<201;i++)
	A[i] = 1000000;
    vector<map<int,int>> verVec;
    verVec.resize(201);
    vector<int> vxs; 
    vxs.reserve(200);
    int nV=0;
    while(fgets(tmpInt, 1024, fd)){
	nV++;
	char* tok;
	tok=strtok(tmpInt, delem);
	int iV = atoi(tok);
	while((tok=strtok(NULL, delem))!=NULL ){
	    int tmpV, length;
	    sscanf(tok, "%d,%d", &tmpV, &length);
	    verVec[nV].insert(pair<int,int>(tmpV, length));
	}
    }
    for(int i=2;i<=nV;i++)
	vxs.push_back(i);
    vector<bool> VX;
    VX.resize(201,true);
    VX[1] = false;
    for(auto it=verVec[1].begin();it!=verVec[1].end();it++)
	A[it->first] = it->second;
    std::make_heap(vxs.begin(),vxs.end(),greater1());
    while(!vxs.empty()){
	std::make_heap(vxs.begin(),vxs.end(),greater1());
//	sort_heap(vxs.begin(),vxs.end(),less1());
	int nextV = vxs.front();
	pop_heap(vxs.begin(),vxs.end(),greater1());
	vxs.pop_back();
	VX[nextV] = false;
	for(auto it=verVec[nextV].begin();it!=verVec[nextV].end();it++){
	    if(VX[it->first])
		A[it->first] = min(A[it->first], A[nextV]+it->second);    
	}
    }
    int index[10]={7,37,59,82,99,115,133,165,188,197};
    map<int, int> result;
    for(int i=2;i<=nV;i++)
	result.insert(pair<int,int>(A[i],i));
    for(auto it=result.begin();it!=result.end();it++)
	cout<<it->second<<" "<<it->first<<endl;
    for(int i=0;i<10;i++)
	cout<<A[index[i]]<<",";
    cout<<endl;
    return 0;
}
