/*************************************************************************
	> File Name: c11.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sat 31 Dec 2016 01:42:18 AM PST
 ************************************************************************/

#include<iostream>
#include<functional>

void func(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
    static int foo_func(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ")" << std::endl;
        return a;
    }
    void operator()(void)
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};

class Bar
{
public:
    int operator()(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ")" << std::endl;
        return a;
    }
};

class A
{
    std::function<void(void)> callback_;
public:
    A(const std::function<void(void)> &f):callback_(f){}
    void notify(void)
    {
        callback_();
    }
};

class AA
{
public:
    int i_ = 0;

    void output(int x, int y)
    {
        std::cout << __FUNCTION__ << "  x:" << x <<"  "<< "y:" << y << std::endl;
    }
};
int main(int argc, char* argv[])
{
    std::function<void(void)> fr1 = func;//normal function
    fr1();

    std::function<int(int)> fr2 = Foo::foo_func;//class static function
    std::cout << fr2(123) << std::endl;

    Bar bar;
    fr2=bar; //operator function
    std::cout << fr2(123) << std::endl;    

    Foo foo;
    A aa(foo);
    aa.notify();

    AA aa1;
    std::function<void(int,int)> fr = std::bind(&AA::output, &aa1, std::placeholders::_2, std::placeholders::_1);
    fr(1 ,2); 

    std::function<int &(void)> fr_i = std::bind(&AA::i_, &aa1);
    fr_i() = 666;
    std::bind(&AA::output, &aa1, std::placeholders::_2, std::placeholders::_1)(3,4);

    return 0;
}
