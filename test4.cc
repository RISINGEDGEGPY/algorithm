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
#include <iostream>
#include <string>
#include<stdlib.h>
#include<vector>
#include<set>
#include<map>
#include<exception>
#include<algorithm>
#include<fstream>
#include<stdio.h>
using namespace std;

int quickSortFirst(int* intVec,int start,int size){
    if(size<=1)
	return 0;
    if(size==2){
	if(intVec[start]>intVec[start+1])
	    swap(intVec[start],intVec[start+1]);
	return 1;
    }
    int pivot= intVec[start];
    int i=start+1,j=start+1;
    for(;j<start+size;j++){
	if(intVec[j]<pivot){
	    swap(intVec[j],intVec[i]);
	    i++;
	}
    }
    swap(intVec[start],intVec[i-1]);
    int result = size-1;
    if((i-start-1)>2)
	result+=  quickSortFirst(intVec,start,i-start-1);
    result+=quickSortFirst(intVec,i,j-i);
    return result;
}

int quickSortLast(int* intVec,int start,int size){
    if(size<=1)
	return 0;
    if(size==2){
	if(intVec[start]>intVec[start+1])
	    swap(intVec[start],intVec[start+1]);
	return 1;
    }
    swap(intVec[start],intVec[start+size-1]);
    int pivot= intVec[start];
    int i=start+1,j=start+1;
    for(;j<start+size;j++){
	if(intVec[j]<pivot){
	    swap(intVec[j],intVec[i]);
	    i++;
	}
    }
    swap(intVec[start],intVec[i-1]);
    int result = size-1;
    if((i-start-1)>2)
	result+=  quickSortLast(intVec,start,i-start-1);
    result+=quickSortLast(intVec,i,j-i);
    return result;
}

int quickSort3(int* intVec,int start,int size){
    if(size<=1)
	return 0;
    if(size==2){
	if(intVec[start]>intVec[start+1])
	    swap(intVec[start],intVec[start+1]);
	return 1;
    }
    int a=intVec[start],b=intVec[start+(size+1)/2],c=intVec[start+size-1];
    if(a>c)
	swap(a,c);
    if(a>b)
	swap(a,b);
    if(b>c)
	swap(b,c);
    intVec[start+(size+1)/2]=a;intVec[start+size-1]=c;
    intVec[start]=b;
    int pivot= b;
    int i=start+1,j=start+1;
    for(;j<start+size;j++){
	if(intVec[j]<pivot){
	    swap(intVec[j],intVec[i]);
	    i++;
	}
    }
    swap(intVec[start],intVec[i-1]);
    int result = size-1;
    if((i-start-1)>2)
	result+=  quickSort3(intVec,start,i-start-1);
    result+=quickSort3(intVec,i,j-i);
    return result;
}

int main(int argc, char** argv) {
    FILE* fd = fopen("/home/pengyuan/Downloads/QuickSort.txt", "r");
    char tmpInt[100];
    int intVec1[10001];
    int intVec2[10001];
    int small1[20]={ 2,1,12,13,16,10,9,5,18,8,17,20,19,3,4,11,14,6,7,15};
    int small2[20]={ 2,1,12,13,16,10,9,5,18,8,17,20,19,3,4,11,14,6,7,15};
    int small3[20]={ 2,1,12,13,16,10,9,5,18,8,17,20,19,3,4,11,14,6,7,15};
    cout<<"First:" <<quickSortFirst(small1,0,20) <<endl;
    cout<<"Last:" <<quickSortLast(small2,0,20) <<endl;
    cout<<"Third:" <<quickSort3(small3,0,20) <<endl;
    int intVec3[10001];
    int i=0;
    while(fgets(tmpInt, 100, fd)){
	intVec1[i]=atoi(tmpInt);
	intVec2[i]=atoi(tmpInt);
	intVec3[i]=atoi(tmpInt);
	i++;
    }
    cout<<"First:" <<quickSortFirst(intVec1,0,i) <<endl;
    for(int i=0;i<100;i++)
	cout<<intVec1[i]<<' ';
    cout<<"Last:" <<quickSortLast(intVec2,0,i) <<endl;
    for(int i=0;i<100;i++)
	cout<<intVec2[i]<<' ';
    cout<<"Third:" <<quickSort3(intVec3,0,i) <<endl;
    for(int i=0;i<100;i++)
	cout<<intVec3[i]<<' ';
    return 0;
}


