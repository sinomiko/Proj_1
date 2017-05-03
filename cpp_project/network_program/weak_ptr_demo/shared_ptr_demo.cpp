/*************************************************************************
	> File Name: weak_ptr_demo.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 25 Oct 2016 07:30:35 PM PDT
 ************************************************************************/

#include<string>
#include<iostream>
#include<memory>
class parent;
class children;

typedef std::shared_ptr<parent> parent_ptr;
typedef std::shared_ptr<children> children_ptr;

class parent
{
public:
    ~parent() { std::cout <<"destroying parent\n"; }

public:
    children_ptr children;
};

class children
{
public:
    ~children() { std::cout <<"destroying children\n"; }

public:
    parent_ptr parent;
};


void test()
{
    parent_ptr father(new parent());
    children_ptr son(new children);

    father->children = son;
    son->parent = father;
}

int main()
{
    std::cout<<"begin test...\n";
    test();
    std::cout<<"end test.\n";
    return 0;
}
