#pragma once
#include <iostream>

template<typename T>
struct MyClass;             // primary template

template<typename T, std::size_t SZ>
struct MyClass<T[SZ]>       // partial specialization for arrays of known bounds
{
    static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]>    // partial spec. for references to arrays of known bounds
{
    static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template<typename T>
struct MyClass<T[]>         // partial specialization for arrays of unknown bounds
{
    static void print() { std::cout << "print() for T[]\n"; }
};

template<typename T>
struct MyClass<T(&)[]>      // partial spec. for references to arrays of unknown bounds
{
    static void print() { std::cout << "print() for T(&)[]\n"; }
};

template<typename T>
struct MyClass<T*>         // partial specialization for pointers
{
    static void print() { std::cout << "print() for T*\n"; }
};


template<typename T1, typename T2, typename T3>
void fooArray(int a1[7], int a2[],    // pointers by language rules
    int(&a3)[42],          // reference to array of known bound
    int(&x0)[],            // reference to array of unknown bound
    T1 x1,                  // passing by value decays
    T2& x2, T3&& x3)        // passing by reference
{
    MyClass<decltype(a1)>::print();      // uses MyClass<T*>
    MyClass<decltype(a2)>::print();      // uses MyClass<T*>
    MyClass<decltype(a3)>::print();      // uses MyClass<T(&)[SZ]>
    MyClass<decltype(x0)>::print();      // uses MyClass<T(&)[]>
    MyClass<decltype(x1)>::print();      // uses MyClass<T*>
    MyClass<decltype(x2)>::print();      // uses MyClass<T(&)[]>
    MyClass<decltype(x3)>::print();      // uses MyClass<T(&)[]>
}