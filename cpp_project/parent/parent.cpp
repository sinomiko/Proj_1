/*************************************************************************
	> File Name: parent.cpp
	> Author: Miko Song
	> Mail: xiaoming.song@ericsson.com 
	> Created Time: Wed 21 Sep 2016 10:29:57 PM PDT
 ************************************************************************/
#include<unistd.h>  
#include<stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <errno.h>  
#include <iostream>  
#include <string>  
#define MASTER_WRITE 11  
int main(int argc, char** argv)  
{  
    int fildes[2];  
    pid_t pid;  
    int i,j;  
    char buf[256];  
    if(pipe(fildes)<0)  
    {  
        fprintf(stderr,"pipe error!\n");  
        return 1;  
    }  
    if((pid = fork())<0)  
    {  
        fprintf(stderr,"fork error!\n");  
        return 1;  
    }  
    if(pid == 0)  
    {  
        close(fildes[1]); 
  
        argv[0] = "child";
  
        if(-1 == dup2(fildes[0],MASTER_WRITE)) 
        {  
            printf("dup2 error%s\n", strerror(errno));  
        }  
        if(-1 ==close(fildes[0]))  
        {  
            printf("child colse(fildes[0]) failed:%s\n", strerror(errno));  
        }  
        execvp("/home/test/pipetest/child1", argv);  
        close(fildes[MASTER_WRITE]);  
        return 1;  
    }  
  
    if(-1 == close(fildes[0]))  
    {  
        printf("parent colse(fildes[0]) failed:%s\n", strerror(errno));  
    }  
    while(1)  
    {  
        std::string str;  
        getline(std::cin,str);  
        if(str.compare("exit") == 0)  
        {  
            int iOut = -1;  
            write(fildes[1],&iOut, sizeof(int));  
            break;  
        }  
        int length = str.length();  
        write(fildes[1],&length, sizeof(int));  
        write(fildes[1],str.c_str(), str.length());  
    }  
    waitpid(pid,NULL,0);  
    printf("parent to exit!\n");  
    close(fildes[1]);  
    return 0;  
}  