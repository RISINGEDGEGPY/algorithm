
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

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/mwis.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/stanford-algs-master/testCases/course3/assignment3HuffmanAndMWIS/question3/input_random_48_10000.txt","r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/test2Sum2.txt", "r");
    char tmpInt[1024];
    int index[8]={1,2,3,4,17,117,517,997};
    fgets(tmpInt, 1024, fd);
    int num = atoi(tmpInt);
    vector<unsigned long> nodes;
    nodes.reserve(num+1);
    while(fgets(tmpInt, 1024, fd)){
	unsigned long key= atol(tmpInt);
	nodes.push_back(key);
    }
    assert(nodes.size()==num);
    vector<unsigned long> scores(num+1, 0);
    scores[0]=nodes[0];
    scores[1] = max(nodes[0],nodes[1]);
    for(int i=2;i<num;i++)
	scores[i] = max(scores[i-1],scores[i-2]+nodes[i]);
    vector<bool> used(num+1,false);
    int i=num-1;
    while(i>1){
	if(scores[i-1]>=scores[i-2]+nodes[i])
	    i--;
	else{ used[i]=true;i-=2;}
    }
    if(used[2] || nodes[0]>nodes[1])
	used[0]=true;
    else used[1] =true;
    for(int i=0;i<8;i++){
	if(index[i]<= num && used[index[i]-1])
	    cout<<"1";
	else cout<<"0";
    }
    cout<<endl;
    return 0;
}
