/*************************************************************************
	> File Name: placement-new.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 09 May 2017 11:41:30 PM PDT
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;
const int N = 10;
class Foo{
private:
    char m_cc;
    float m_f;
public:
    void print()
    {
        cout<<"ADDR: " << this <<endl;
    }
    void set_f(float f)
    {
         cout<<"set f val:"<<f<<endl;
         m_f=f;
    }
    void get_f()
    {
        cout<<"get f val:"<<m_f<<endl;
    }
};

int main()
{
    char* buf = new char[sizeof(Foo)*N];
    memset(buf,0,sizeof(Foo)*N);
    Foo* pfoo=new (buf)Foo;
    pfoo->print();
    pfoo->set_f(1.0f);
    pfoo->get_f();
    pfoo->~Foo();
    delete[]buf;
    return 0;
}
