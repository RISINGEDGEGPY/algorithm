
#include<stdlib.h>
#include<vector>
#include<assert.h>
#include<set>
#include<map>
//#include<multimap>
#include<exception>
#include<algorithm>
#include<fstream>
#include<stdio.h>
#include<unordered_set>
#include<utility>
#include<iostream>

//#include <omp.h>
using namespace std;

class Edge{
public:
    Edge(int n1,int n2,int cost): _n1(n1), _n2(n2), _cost(cost){}
    Edge(){}
    ~Edge(){}
    int _n1;
    int _n2;
    int _cost;
    bool operator()(const Edge& e1, const Edge& e2){
	return e1._cost>e2._cost;
    }
} myObj;

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/edges.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/stanford-algs-master/testCases/course3/assignment1SchedulingAndMST/question3/input_random_64_100000.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/test2Sum2.txt", "r");
    char tmpInt[1024];
    vector<int> mark(20001,0);
    fgets(tmpInt, 1024, fd);
    int nNodes, nEdges; 
    sscanf(tmpInt, "%d %d\n", &nNodes, &nEdges );
    int n1,n2,cost;
    vector<vector<pair<int, int>>> vMaps;
    vector<bool> vStatus(nNodes+1, false);
    vMaps.resize(nNodes+2);
    while(fgets(tmpInt, 1024, fd)){
	sscanf(tmpInt, "%d %d %d\n", &n1, &n2, &cost );
	vMaps[n1].push_back(pair<int, int>(n2, cost));
	vMaps[n2].push_back(pair<int, int>(n1, cost));
    }
    int count=nNodes-1;
    vStatus[1]=true;
    vector<Edge> heapEdges;
    heapEdges.reserve(nEdges/2);
    for(auto it = vMaps[1].begin();it!=vMaps[1].end();it++){
	Edge tmp = {1,it->first, it->second};
	heapEdges.push_back(tmp);
    }
    make_heap(heapEdges.begin(), heapEdges.end(), myObj);
    //sort_heap(heapEdges.begin(), heapEdges.end(), myObj);
    Edge tmp = heapEdges[0];
    long result=0;
    while(count>0){
	count--;
	Edge tmp;
	do{
	    assert(!heapEdges.empty());
	    tmp = heapEdges.front();
	    pop_heap(heapEdges.begin(), heapEdges.end(), myObj);
	    heapEdges.pop_back();
	}while(vStatus[tmp._n1] && vStatus[tmp._n2]);
	result += tmp._cost;
	int pivot = vStatus[tmp._n1] ? tmp._n2 : tmp._n1;
	vStatus[pivot] = true;
	for(auto it = vMaps[pivot].begin();it!=vMaps[pivot].end();it++){
	    if(vStatus[it->first])
		continue;
	    Edge t2 = {pivot, it->first, it->second};
	    heapEdges.push_back(t2);
	    push_heap(heapEdges.begin(), heapEdges.end(), myObj);
	}
    }
    cout<<"Result: "<<result<<endl;
}
