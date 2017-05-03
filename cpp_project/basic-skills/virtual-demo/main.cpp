/*************************************************************************
	> File Name: main.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Wed 19 Apr 2017 12:33:07 AM PDT
 ************************************************************************/

#include <iostream>
using namespace std;
 
class Base1 {
public:
            virtual void f() { cout << "Base1::f" << endl; }
            virtual void g() { cout << "Base1::g" << endl; }
            virtual void h() { cout << "Base1::h" << endl; }
 
};
 
class Base2 {
public:
            virtual void f() { cout << "Base2::f" << endl; }
            virtual void g() { cout << "Base2::g" << endl; }
            virtual void h() { cout << "Base2::h" << endl; }
};
 
class Base3 {
public:
            virtual void f() { cout << "Base3::f" << endl; }
            virtual void g() { cout << "Base3::g" << endl; }
            virtual void h() { cout << "Base3::h" << endl; }
};
 
 
class Derive : public Base1, public Base2, public Base3 {
public:
            virtual void f() { cout << "Derive::f" << endl; }
            virtual void g1() { cout << "Derive::g1" << endl; }
};
 
 
typedef void(*Fun)(void);
 
int main()
{
            Fun pFun = NULL;
 
            Derive d;
            int** pVtab = (int**)&d;
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
            //pFun = (Fun)pVtab[0][0];
            pFun();

            Fun fun = NULL; 
            fun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
            //pfun=(Fun)*((int*)*(int*)(&d)+1);
            //pFun = (Fun)pVtab[0][1];
            cout<<fun<<endl;
            fun();
           
            pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
            //pFun = (Fun)pVtab[0][2];
            pFun();
         
            pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
            //pFun = (Fun)pVtab[0][3];
            pFun();
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+0)+4);
            //pFun = (Fun)pVtab[0][4];
            cout<<pFun<<endl;
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
            //pFun = (Fun)pVtab[1][0];
            pFun();
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
            //pFun = (Fun)pVtab[1][1];
            pFun();
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+1)+2);
            //pFun = (Fun)pVtab[1][2];
            pFun();
 
            pFun = (Fun)*((int*)*(int*)((int*)&d+1)+3);
            //pFun = (Fun)pVtab[1][3];
            cout<<pFun<<endl;
 
 
 
            //pFun = (Fun)pVtab[2][0];
            pFun = (Fun)*((int*)*(int*)((int*)&d+2)+0);
            pFun();
 
            //pFun = (Fun)pVtab[2][1];
            pFun = (Fun)*((int*)*(int*)((int*)&d+2)+1);
            pFun();
 
            //pFun = (Fun)pVtab[2][2];
            pFun = (Fun)*((int*)*(int*)((int*)&d+2)+2);
            pFun();
 
            //pFun = (Fun)pVtab[2][3];
            pFun = (Fun)*((int*)*(int*)((int*)&d+2)+3);
            cout<<pFun<<endl;
 
            return 0;
}
