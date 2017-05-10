/*************************************************************************
	> File Name: stack-heap.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Wed 10 May 2017 02:56:47 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
int g_int1 = 10;
int g_int2 = 9;
char g_char = 'a';
int main(int argc, char* argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int *c = a + 5;
    *c = 100; 
    int *a1 = new int(2);
    int *a2 = new int(2);
    delete a1,a2;
    return 0;
} 
