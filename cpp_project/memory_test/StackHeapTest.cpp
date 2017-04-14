/*************************************************************************
	> File Name: StackHeapTest.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Fri 14 Apr 2017 12:22:04 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

int main(int argc, char * argv[])
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    cout<<&a[0]<<"\t"<<&a[1]<<"\t"<<endl;

    int* b = new int[10]{1,2,3,4,5,6,8,9,10};
    cout<<&b[0] <<"\t"<<&b[1] <<endl;
    cout<< &b<<endl;

    int* c = new int[10]{1,2,3,4,5,6,8,9,10};
    cout<<&c[0] <<"\t"<<&c[1] <<endl;
    cout<<&c<<endl;

    return 0;

}
/*
 * printOut:
 *
 * 0x7fff566e3750  0x7fff566e3754
 * 0x1275010       0x1275014
 * 0x7fff566e3788
 * 0x1275040       0x1275044
 * 0x7fff566e3780
 *
*/
