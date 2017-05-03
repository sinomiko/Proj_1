/*************************************************************************
	> File Name: c11_2.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sun 01 Jan 2017 01:18:43 AM PST
 ************************************************************************/

#include<iostream>
#include<type_traits>
void print()
{

    std::cout << __FUNCTION__ <<" "<< "empty " << std::endl;
}

template <typename T, typename ...  Args>
void print(T head, Args ... rest)
{
    std::cout << __FUNCTION__ <<" "<< head <<std::endl;
    print(rest...);
}

template <class T>
void printarg (T t)
{
    std::cout << __FUNCTION__ <<" "<< t << std::endl;
}

template <class ... Args>
void expand(Args ... args)
{
    int arr[] = {(printarg(args), 0)...}; 
}
int main(int argc, char* argv[])
{
    std::cout <<"is_const   "<< std::is_const<const int>::value << std::endl;
    print(1,2,3,4);
    std::cout << __FUNCTION__ <<" "<< std::endl;
    expand(1,2,3,4);
    return 0;
}
