#pragma once
#include <iostream>
using namespace std;

/************************************************************************/
/* 4.1.1 Variadic Templates                                                                      */
/************************************************************************/
// void print()
// {
// }

template<typename T, typename... Types>
void print(T firstArg, Types... args) 
{
    cout << firstArg << "----------"<<sizeof...(args)<<endl; 
    //print(args...);
    if constexpr(sizeof...(args) > 0) {
        print(args...);   //code only available if sizeof...(args)>0 (since C++17) 
    }
}

/************************************************************************/
/* 4.1.2 Overloading Variadic and Nonvariadic Templates                                                                     */
/************************************************************************/
template<typename T>
void print2(T arg)
{
    std::cout << arg << endl;  //print passed argument
}

template<typename T, typename... Types>
void print2(T firstArg, Types... args)
{
    print2(firstArg);                // call print() for the first argument
    cout << sizeof...(args) << endl;
    print2(args...);                 // call print() for remaining arguments
}