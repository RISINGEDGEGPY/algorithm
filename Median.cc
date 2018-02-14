#include <iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<string.h>
#include<stdio.h>
using namespace std;

struct greater1{
    bool operator()(const int & a, const int& b)const{
	return a>b;
    }
};

int main(){
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/Mediantest.txt", "r");
    char tmpInt[1024];
    vector<int> nums;
    nums.reserve(10000);
    while(fgets(tmpInt, 1024, fd)){
	nums.push_back(atoi(tmpInt));	
    }
    vector<int> leftStack,rightStack;
    leftStack.reserve(5001);
    rightStack.reserve(5001);
    unsigned long long sum=0;
    sum=nums[0]+min(nums[0],nums[1]);
    leftStack.push_back(min(nums[0],nums[1]));
    rightStack.push_back(max(nums[0],nums[1]));
    vector<int> results;
    results.push_back(nums[0]);
    results.push_back(leftStack.front());
    for(int i=2;i<nums.size();i++){
	if(nums[i]<rightStack.front()){
	    leftStack.push_back(nums[i]);
	    push_heap(leftStack.begin(),leftStack.end());
	}else{
	    rightStack.push_back(nums[i]);
	    push_heap(rightStack.begin(),rightStack.end(),greater1());
	}
	if(leftStack.size()<rightStack.size()){
	    leftStack.push_back(rightStack.front());
	    push_heap(leftStack.begin(),leftStack.end());
	    pop_heap(rightStack.begin(),rightStack.end(),greater1());
	    rightStack.pop_back();
	}else if(rightStack.size()<leftStack.size()-1){
	    rightStack.push_back(leftStack.front());
	    push_heap(rightStack.begin(),rightStack.end(),greater1());
	    pop_heap(leftStack.begin(),leftStack.end());
	    leftStack.pop_back();
	}
	sum+= leftStack.front();
	results.push_back(leftStack.front());
    }
    for(int i=0;i<10;i++)
	cout<<results[i]<<endl;
    cout<<"Sum: "<<sum<<endl;
}
    
