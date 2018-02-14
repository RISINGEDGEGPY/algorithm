
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

class Node{
public:
    Node(){}
    Node(unsigned long key, Node* left, Node* right):_value(key),_left(left),_right(right){}
    ~Node(){}
    unsigned long _value;
    Node* _left;
    Node* _right;
};

int getDepth(Node* root){
    if(root ==NULL)
	return 0;
    if(root->_left==NULL && root->_right==NULL)
	return 0;
    return 1+ max(getDepth(root->_left), getDepth(root->_right));
}

int getShortest(Node* root){
    if(root==NULL || root->_left==NULL || root->_right==NULL)
	return 0;
    return 1+ min(getShortest(root->_left), getShortest(root->_right));
}

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/huffman.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/stanford-algs-master/testCases/course3/assignment1SchedulingAndMST/question3/input_random_64_100000.txt", "r");
    //FILE* fd = fopen("/home/pengyuan/Downloads/Algorithm/test2Sum2.txt", "r");
    char tmpInt[1024];
    fgets(tmpInt, 1024, fd);
    int num = atoi(tmpInt);
    map<unsigned long, Node*> nodeMap;
    while(fgets(tmpInt, 1024, fd)){
	unsigned long key= atol(tmpInt);
	Node* tmpNode = new Node(key, NULL,NULL);
	nodeMap.insert(pair<unsigned long, Node*>(key, tmpNode));
    }
    assert(nodeMap.size()==num);
    while(nodeMap.size()>1){
	auto it1 = nodeMap.begin();
	auto it2 = it1++;
	Node* tmpNode = new Node(it1->first+it2->first, it1->second, it2->second);
	nodeMap.erase(it1);
	nodeMap.erase(it2);
	nodeMap.insert(pair<unsigned long, Node*>(tmpNode->_value, tmpNode));
    }
    cout<<"The depth is : "<<getDepth(nodeMap.begin()->second)<<endl;
    cout<<"The shortest one is : "<<getShortest(nodeMap.begin()->second)<<endl;
    return 0;

}
