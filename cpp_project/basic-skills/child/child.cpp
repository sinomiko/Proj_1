#include <unistd.h>

#include <stdio.h>
#include <string.h>

#define MASTER_WRITE 11

int main(int argc, char** argv)
{
    for(int i=0; i<argc; ++i)
    {
        printf("argv[%d]=%s\n",i,argv[i]);
    }

    char buf[255];
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int length = 0;
        read(MASTER_WRITE, &length, sizeof(int)); 
        if(-1 == length)
        {
            printf("child exist\n");
            break;
        }
        else if( length >0)
        {
            read(MASTER_WRITE, buf, length);
            printf("cur=%d,,,,data = %s,,,\n",length, buf);
        }
    }
}

