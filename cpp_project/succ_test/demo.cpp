/*************************************************************************
	> File Name: demo.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 03 Jan 2017 04:15:52 AM PST
 ************************************************************************/

#include<iostream>
#include <typeinfo>
using namespace std;

class A{
private:

    virtual void vPrivateF(){
        cout << "A:: vPrivateF" <<endl;
    }
    void PrivateF(){
        cout << "A:: PrivateF" <<endl;
    }    
public:
    virtual void vPublicF(){
         cout << "A:: vPublicF" <<endl;
    }
     void PublicF(){
         cout << "A:: PublicF" <<endl;
    }  

};

class B: public A{
public:
    virtual void vPublicF(){
        cout << "B:: vPublicF" <<endl;
    }
     void PublicF(){
        cout << "B:: PublicF" <<endl;
    }
};

typedef void (*FUNC)();

int main(int argc, char* argv[])
{
    B* b = new B();
    A* a = dynamic_cast<A*> (b);
    a->A::vPublicF();
    FUNC func = (FUNC)((int*)(*(int*)(*(int*)(b))));
    func();
    FUNC func2 = (FUNC)((int*) (&b) );
    func2();
    B bb;
    FUNC func3 = (FUNC)((int*)(*(int*)(*(int*)(&bb))));
    func3();
    bb.vPublicF();
    cout << endl << typeid( a ).name() << endl;
    cout << endl << typeid( b ).name() << endl;
    return 1;
}


