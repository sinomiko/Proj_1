/*************************************************************************
	> File Name: test.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Wed 15 Mar 2017 02:17:55 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#define MAX_SIZE 1000
int split_up(char* string, char* argv[])
{
    char* p = string;
    int argc = 0;
    char delimer = ',';
    int count = 0;
    char tmp[1024];

    while(*p != '\0')
    {
        if(*p !=delimer){
            tmp[count++] = *p;
        }
        else{
            tmp[count++]='\0';
            argv[argc]=(char*)malloc(sizeof(char)*count);
            memcpy(argv[argc],tmp,count);
            count = 0;
            argc++;
        }
        p++;

    }
    tmp[count++]='\0';
    argv[argc]=(char*)malloc(sizeof(char)*count);
    memcpy(argv[argc++],tmp,count);
    return argc;
}

int main()
{
    char *av[MAX_SIZE];
    char string[] = "this,a,test";
    int i;
    int ac = split_up(string, av);
    printf("The number of token is: %d\n", ac);
    for(i = 0; i < ac; i++)
        printf("\"%s\"\n", av[i]);

    return 0;
}
