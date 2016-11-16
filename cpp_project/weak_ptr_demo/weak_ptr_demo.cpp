/*************************************************************************
	> File Name: weak_ptr_demo.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 25 Oct 2016 07:30:35 PM PDT
 ************************************************************************/

#include<string>
#include<iostream>
#include<memory>
class Parent;
class Children;

typedef std::weak_ptr<Parent> Parent_ptr;
typedef std::shared_ptr<Children> Children_ptr;

class Parent
{
public:
    ~Parent() { std::cout <<"destroying parent\n"; }

public:
    Children_ptr children;
};

class Children
{
public:
    ~Children() { std::cout <<"destroying children\n"; }

public:
    Parent_ptr parent;
};


void test()
{
    std::shared_ptr<Parent> father(new Parent());
    std::shared_ptr<Children> son(new Children());

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
