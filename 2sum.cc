
#include <cstdlib>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <string>
#include <string.h>
#include<stdlib.h>
#include<vector>
#include<set>
#include<map>
//#include<multimap>
#include<exception>
#include<algorithm>
#include<fstream>
#include<stdio.h>
#include<unordered_set>
#include <omp.h>

using namespace std;

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/algo1-programming_prob-2sum.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/stanford-algs-master/testCases/course2/assignment4TwoSum/input_random_68_640000.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/test2Sum2.txt", "r");
    char tmpInt[1024];
    unordered_set<long > pool;
    pool.rehash(5000000);
    vector<long> nums;
    nums.reserve(1000000);
    unsigned long count=0;
    char delem[]="\n";
    vector<int> mark(20001,0);
    while(fgets(tmpInt, 1024, fd)){
	char* tok;
	tok=strtok(tmpInt, delem);
	long num = atol(tok);
	if(pool.find(num)==pool.end()){
	    nums.push_back(num);
	    pool.insert(num);
	}
    }
    //multimap<long,long> aa;
#pragma omp parallel for reduction(+:count)
    for(int i=0;i<nums.size();i++){
	long num = nums[i];
	long p1 = max(-10000-num,num+1);
	long p2 = 10000-num;
	for(long j=p1;j<=p2;j++){
	    if(j==num)
		continue;
	    //cout<<"Key count: "<<pool.count(j)<<endl;
	    if(pool.find( j )!=pool.end() && mark[num+j+10000]==0){
		//aa.insert(pair<long, long>(num, j));
		count++;
		mark[num+j+10000]=1;
	    }
	}
	if(i%1000==0)
	    cout<< "Current num: "<<i<<", count number: "<< count<<endl;
    }
    cout<< "The count number: "<<count<<endl;
    //set<int> bb;
    //for(auto it=aa.begin();it!= aa.end();it++){
    //    bb.insert(it->first+it->second);
    //    cout<<it->first<<" "<<it->second<<endl;
    //}
    //cout<<"Distinct value: "<<bb.size()<<endl;
    //cout<<"map size: "<<aa.size()<<endl;
    return 0;
}
