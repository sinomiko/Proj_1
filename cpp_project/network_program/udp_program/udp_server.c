/*************************************************************************
	> File Name: udp_server.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 14 Mar 2017 11:16:57 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 3490 

void main()
{
    int sockfd; 
    struct sockaddr_in my_addr; 
    struct sockaddr_in their_addr; 
    int sin_size, retval;
    char buf[128];
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT); 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
    bzero(&(my_addr.sin_zero), 8); 
    
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    while(1) { 
        retval = recvfrom(sockfd, buf, 128, 0, (struct sockaddr *)&their_addr, &sin_size);
        printf("Received datagram from %d \n",inet_ntoa(their_addr.sin_addr));
        if (retval == 0) {
            perror ("recvfrom");
            close(sockfd);
            break;
        }
    
        retval = sendto(sockfd, buf, 128, 0, (struct sockaddr *)&their_addr, sin_size);
    }
    
}
