//create
//to build the block and the unrolled list
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#ifndef MAIN_CPP_UNROLLEDLIST_H
#define MAIN_CPP_UNROLLEDLIST_H
using namespace std;
class element{
public:
    char key[100] = "";
    int offset = -1;
    explicit element(const string & the_key = "",int the_offset = -1);
    element & operator = (const element &obj);
    element(const element &obj);
    bool operator < (const element &obj){
        if(strcmp(key,obj.key) < 0)return true;
        else return false;
    }
};

class block{
public:
    element elementarray[300];
    int pre = -1;
    int nxt = -1;
    int num = 0;
    block();
};

class unrolledlist{
public:
    char filename[111] = "";
    explicit unrolledlist(string file);
    void addElement(element &a);
    void findElement(string key,vector<int>&area);
    void deleteElement(element &a);
    void split(int offset);
    void merge(int offset1,int offset2);
    int nxt_offset(int offset){
        fstream filein;
        filein.open(filename,ios::in | ios::out |ios::binary);
        filein.seekg(offset);
        block tmp;
        filein.read(reinterpret_cast<char*>(&tmp),sizeof(block));
        return tmp.nxt;
    }
};


#endif