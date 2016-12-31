/*************************************************************************
	> File Name: c11.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sat 31 Dec 2016 01:42:18 AM PST
 ************************************************************************/

#include<iostream>
#include<map>
#include<vector>
template <typename T, typename U>
auto add(T t, U u) -> decltype(t+u)
{
    return t+u;
} 

template <typename T>
struct Foo
{
    typedef T type;
};

template <typename T>
class A
{
public:
    T m_;
    A()
    {
    }
    A(T t)
    {
        m_ = t;
    }
 
};

template <typename T>
using str_map_t = std::map<std::string, T>;
str_map_t<int> map1;

template <typename T>
using func_t = void (*)(T,T);
func_t<int> func_ptr;

template <typename T = int>
void fun(T t)
{
    std::cout << " fun() --> t:"<< t << std::endl;
}

template <typename T>
struct identity
{
    typedef T type;
};

template <typename T = int>
void func(typename identity<T>::type val, T t=0)
{
    std::cout << " func() --> val:"<< val << std::endl;
    std::cout << " func() --> t:"<< t << std::endl;
}

void func2(std::initializer_list<int> l)
{
    for (auto it = l.begin();it!=l.end();++it)
    {
        std::cout << " iterator: it="<< *it << std::endl;
    }
}

int main(int argc, char* argv[])
{
    int n = 0;
    volatile const int & x = n;
    
    decltype(n) a = n;
    decltype(x) b = n;

    n = 10;

    std::cout << " x: " << x << std::endl;
    std::cout << " a: " << a << std::endl;
    std::cout << " b: " << b << std::endl;

    n = 20;
    std::cout << " x: " << x << std::endl;
    std::cout << " a: " << a << std::endl;
    std::cout << " b: " << b << std::endl;
   
    Foo<A<int>>::type xx;
    xx=A<int>();
    
    Foo<A<int>>::type xx2;
    xx2=A<int>(8);
 
    std::cout << " xx2.m_: " << xx2.m_ << std::endl; 

   
    fun(8); 
    fun<float>(8.8888888);
    
    func(123);
    func(321,123.0);
    identity<double>::type tp = 12.2;
    func<double>(tp,12);

    float y[2][3] =
    {
     {1,2,3},
     {4,5,6},
    };    

    func2({1,2,n});

    std::vector<int> arrs = {1,2,3,4};
    for(auto arr : arrs)  //auto , auto & , const auto &
        std::cout << " arr: " << arr << std::endl;

    return 0;
/* output: 
 x: 10
 a: 0
 b: 10
 x: 20
 a: 0
 b: 20
 xx2.m_: 8
 fun() --> t:8
 fun() --> t:8.88889
 func() --> val:123
 func() --> t:0
 func() --> val:321
 func() --> t:123
 func() --> val:12.2
 func() --> t:12
 iterator: it=1
 iterator: it=2
 iterator: it=20
*/
}
