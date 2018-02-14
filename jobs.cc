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
#include<utility>
//#include <omp.h>
using namespace std;

bool greater1(const pair<int,int>& w_l1, const pair<int,int>& w_l2){
    int r1=w_l1.first-w_l1.second;
    int r2=w_l2.first-w_l2.second;
    if(r1>r2)
	return true;
    else if(r1<r2)
	return false;
    return w_l1.first>w_l2.first;
}
bool greater2(const pair<int,int>& w_l1, const pair<int,int>& w_l2){
    double r1 = w_l1.first/(double)w_l1.second;
    double r2 = w_l2.first/(double)w_l2.second;
    return r1>r2;
}

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/jobs.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/stanford-algs-master/testCases/course3/assignment1SchedulingAndMST/questions1And2/input_random_44_10000.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/test2Sum2.txt", "r");
    char tmpInt[1024];
    vector<int> mark(20001,0);
    fgets(tmpInt, 1024, fd);
    int num_jobs = atoi(tmpInt);
    int weight, length;
    vector<pair<int, int>> jobs;
    while(fgets(tmpInt, 1024, fd)){
	sscanf(tmpInt, "%d %d\n", &weight, &length );
	jobs.push_back(std::make_pair(weight, length));
    }
    sort( jobs.begin(), jobs.end(), greater1);
    unsigned long time = 0;
    unsigned long sum = 0;
    for(auto iter = jobs.begin();iter!=jobs.end();iter++){
	time+= iter->second;
	sum += iter->first * time;
    }
    cout<< "The (weight-length) result: "<< sum<<endl;

    sort( jobs.begin(), jobs.end(), greater2);
    time = 0;
    sum=0;
    for(auto iter = jobs.begin();iter!=jobs.end();iter++){
	time+= iter->second;
	sum += iter->first * time;
    }
    cout<< "The (weight/length) result: "<< sum<<endl;
}
