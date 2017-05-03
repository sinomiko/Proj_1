/*************************************************************************
	> File Name: switch_test.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Thu 13 Apr 2017 06:11:25 PM PDT
 ************************************************************************/

#include<stdio.h>
int main(int argc, char * argv[])
{
    int a;
    scanf("%d", &a);
    switch(a){
    case 1:
        printf("1 \n");
    case 3:
        printf("3 \n");
        break;
    case 2:
        printf("2 \n");
        break;
    }
    return 1;
}
