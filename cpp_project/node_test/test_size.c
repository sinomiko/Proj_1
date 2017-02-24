/*************************************************************************
	> File Name: test_size.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Thu 19 Jan 2017 12:33:52 AM PST
 ************************************************************************/

#include<stdio.h>

typedef struct Node{
    int num;
    Node * Next; 
}Node;

int main(int argc, char *argv[])
{
//    Node* header = NULL;
//    header = (Node*)malloc(sizeof(Node));
    printf("size:%d, \n", sizeof(Node));
    printf("size:%d, \n", sizeof(Node*));
    printf("size:%d, \n", sizeof(Node**));
    return 0;
}
