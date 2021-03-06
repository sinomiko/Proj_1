// templatesLearningFrame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include <iostream>

#include <string>

#include <array>
#include <vector>
#include <map>
#include <set>
#include "arrays.hpp"
//using namespace std;
//4.1.1 Variadic Templates by Example
void print()
{
}

//4.1.2 Overloading Variadic and Nonvariadic Templates
template<typename T>
void print(T arg)
{
    std::cout << arg << '\n';  //print passed argument
}

template<typename T, typename... Types>
void print(T firstArgs, Types... args)
{
    print(firstArgs);
    print(args...);
}

//4.1.3 Operator sizeof…
/*
template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << sizeof...(Types) <<
        '\n';  //print number of remaining types
    std::cout << sizeof...(args) << '\n';   //print number of remaining args…
}
*/

// 4.2 Fold Expressions C++17
template<typename... T>
auto foldSum(T... s) {
    return (... + s);   // ((s1 + s2) + s3) ...
}

// define binary tree structure and traverse helpers:
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int i = 0) : value(i), left(nullptr), right(nullptr) {
    }
};
auto left = &Node::left;
auto right = &Node::right;
// traverse tree, using fold expression:
template<typename T, typename... TP>
Node* traverse(T np, TP... paths) {
    return (np->*...->*paths); // np ->* paths1 ->* paths2 …
}

//4.4 Variadic Class Templates and Variadic Expressions
//4.4.1 Variadic Expressions
template<typename... T>
void printDoubled(T const&... args)
{
    print(args +args...);
}

template<typename... T>
void addOne(T const&... args)
{
    //print(args + 1...);    // ERROR: 1… is a literal with too many decimal points
    print(args + 1 ...);   // OK
    print((args + 1)...);  // OK
}

template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1, TN...)
{
    return (std::is_same<T1, TN>::value && ...);  // since C++17
}

//4.4.2 Variadic Indices
template<typename C, typename... Idx>
void printElems(C const& coll, Idx... idx)
{
    print(coll[idx]...);
}

// template<std::size_t... Idx, typename C>
// void printIdx(C const& coll)
// {
//     print(coll[Idx]...);
// }

//4.4.3 Variadic Class Templates
template<std::size_t...>
struct  Induces {};

template <typename T, std::size_t... Idx>
void printByIdx(T t, Induces<Idx...>)
{
    print(std::get<Idx>(t)...);
}

//4.4.4 Variadic Deduction Guides
/************************************************************************
namespace std {
  template<typename T, typename… U> array(T, U…)
   -> array<enable_if_t<(is_same_v<T, U> && …), T>,
             (1 + sizeof…(U))>;
}

std::array<int, 3> a{42,45,77};
*/

//4.4.5 Variadic Base Classes and using
/************************************************************************
// define class that combines operator() for variadic base classes:
template<typename… Bases>
struct Overloader : Bases…
{
      using Bases::operator()…;  // OK since C++17
};

// combine hasher and equality for customers in one type:
  using CustomerOP = Overloader<CustomerHash,CustomerEq>;
*/


/************************************************************************
Chapter 5
Tricky Basics
5.1 Keyword typename
template<typename T>
class MyClass {
  public:
    …
    void foo() {
      typename T::SubType* ptr;
      
}
**/

//5.2 Zero Initialization
/************************************************************************
call explicitly a default constructor for built-in types that initializes them with zero (or false for bool or nullptr for pointers)
T x{};      // x is zero (or false) if T is a built-in type

This way of initialization is called value initialization,

Before C++11, the syntax to ensure proper initialization was
T x = T();      // x is zero (or false) if T is a built-in type

通过将构造函数声明为explicit，来防止隐式类型转换。

To ensure that a member of a class template, for which the type is parameterized, gets initialized, you can define a default constructor that uses a braced initializer to initialize the member:
private:
    T x;
  public:
    MyClass() : x{} {  // ensures that x is initialized even for built-in types

The pre-C++11 syntax
MyClass() : x() {

Since C++11, you can also provide a default initialization for a nonstatic member
private:
    T x{};            // zero-initialize x unless otherwise specified

default arguments cannot use that syntax.
template<typename T>
void foo(T p{}) {      //ERROR

Instead, we have to write:
T p = T{} ////OK (must use T() before C++11)
*/

/************************************************************************
5.3 Using this->
For class templates with base classes that depend on template parameters, 
using a name x by itself is not always equivalent to this->x, even though a member x is inherited.
继承基类模板的成员函数或者成员变量，需要加上this-> or Base<T>::
*/

/************************************************************************
5.4 Templates for Raw Arrays and String Literals 原始数组和字符串字面量模板
if the template parameters are declared as references, 
the arguments don’t decay. That is, a passed argument of "hello" has type char const[6]
如果参数模板含有引用，参数类型不会退化
只有通过传值，类型退化，才能使string literals（字符串字面量）转化为char const*

Note that you can also provide templates that specifically deal with raw arrays or string literals
提供一个特别处理数组和字符串字面量的模板
    template<typename T,
    int N,
    int M> bool less (T(&a)[N], T(&b)[M]){}

如果只是用于字符串字面量
template<int N, int M>
bool less (char const(&a)[N], char const(&b)[M])
*/


/************************************************************************

*/
/************************************************************************

*/
/************************************************************************

*/
int main()
{
    //4.2
    // init binary tree structure:
    Node* root = new Node{ 0 };
    root->left = new Node{ 1 };
    root->left->right = new Node{ 2 };

    // traverse binary tree:
    std::cout << "\n traverse(root, left, right)"  << std::endl;
    Node* node = traverse(root, left, right);

    //4.4.1
    std::cout << "\n printDoubled(7.5, std::string('hello')) " << std::endl;
    printDoubled(7.5, std::string("hello"));

    std::cout<< "\n isHomogeneous(43, -1, 'hello') " << isHomogeneous(43, -1, "hello") << std::endl;

    //4.4.2 Variadic Indices
    std::vector<std::string> coll = { "good", "times", "say", "bye" }; 
    std::cout << "\n printElems(coll, 2, 0, 3) " << std::endl;
    printElems(coll, 2, 0, 3);

    //4.4.3 Variadic Class Templates
    std::cout << "Hello World!\n";
    std::array<std::string, 5> arr = { "Hello", "my", "new", "!", "World" }; 
    std::cout << "\n printByIdx(arr, Induces<0, 4, 3>()) " << std::endl;
    printByIdx(arr, Induces<0, 4, 3>());

    //5.4 Templates for Raw Arrays and String Literals
    int a[42];
    MyClass<decltype(a)>::print();       // uses MyClass<T[SZ]> 

    extern int x[];                      // forward declare array
    MyClass<decltype(x)>::print();       // uses MyClass<T[]> 

    fooArray(a, a, a, x, x, x, x);

    return 0;
}

