// templatesLearningFrame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <string>
#include <array>
#include <iostream>

//4.1.1 Variadic Templates by Example
template<typename T>
void print(T arg)
{
    std::cout << arg << '\n';  //print passed argument
}

template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    print(firstArg);                // call print() for the first argument
    print(args...);                 // call print() for remaining arguments
}

template<std::size_t...>
struct  Induces {};

template <typename T, std::size_t... Idx>
void printByIdx(T t, Induces<Idx...>)
{
    print(std::get<Idx>(t)...);
}

int main()
{
  
    //4.4.1
    //printDoubled(7.5, std::string("hello"));
    //isHomogeneous(43, -1, "hello");

    std::cout << "Hello World!\n";
    std::array<std::string, 5> arr = { "Hello", "my", "new", "!", "World" };
    printByIdx(arr, Induces<0, 4, 3>());

    return 0;
}

