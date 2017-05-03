/*************************************************************************
	> File Name: main.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Mon 20 Mar 2017 11:15:01 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(int argc,char * argv[])
{

    struct timeval tv;
    while(1)
  {
          gettimeofday(&tv,NULL);
          printf("time %u:%u\n",tv.tv_sec,tv.tv_usec);
          sleep(2);
     }
    return 0;
}
