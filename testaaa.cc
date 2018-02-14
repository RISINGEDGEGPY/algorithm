#include <algorithm>
#include <iostream>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<string.h>
#include<stdio.h>
#include <iostream>	
#include <vector>		
using namespace std;
struct greater1{	    
    bool operator()(const int& a,const int& b) const{	       
	//return A[a]>A[b];
	return a>b;
    }
};	
int main()
{	 
    vector<int> v;
    v.reserve(10);
    v.push_back(30);
    v.push_back(10);
    v.push_back(50);
    v.push_back(33);
    v.push_back(70);
    v.push_back(80);

    std::make_heap(v.begin(), v.end(), greater1()); // 5 15 10 20 30		
    unsigned int s =  v.size();		  //ALSO NEED TO PASS greater1() to pop()!!!	
    for(unsigned int i = 0; i < s; i++)	   
       	std::pop_heap(v.begin(), v.end(), greater1()); // popping order: 5 10 15 20 30		
    vector<int> vxs; 
    vxs.push_back(32);
    vxs.push_back(32);
    vxs.push_back(32);
    vxs.push_back(32);
    vxs.push_back(32);
    std::make_heap(vxs.begin(), vxs.end(), greater1());
    return 0;
}
