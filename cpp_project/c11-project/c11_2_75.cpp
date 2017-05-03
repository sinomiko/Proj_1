/*************************************************************************
	> File Name: c11_2.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sun 01 Jan 2017 01:18:43 AM PST
 ************************************************************************/

#include<iostream>
//#include<vector>
//#include<cstring>
void PrintT(int &t)
{
    std::cout << "lvalue" << std::endl; 
}

void PrintT(int &&t)
{
    std::cout << "rvalue" << std::endl;
}

template<typename T>
void TestForward(T&&  t)
{
    PrintT(t);
    PrintT(std::forward<T>(t));
    PrintT(std::move(t));
}


int main(int argc, char* argv[])
{
    TestForward(1);
    int x = 1;  
    TestForward(x);
    TestForward(std::forward<int>(x));  
    return 0;
/*
lvalue
rvalue
rvalue
lvalue
lvalue
rvalue
lvalue
rvalue
rvalue
*/
}
