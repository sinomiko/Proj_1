/*************************************************************************
	> File Name: tcp_client.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 14 Mar 2017 10:43:23 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define PORT 7770       /* Server port */
#define MAXDATASIZE 100 /*buffer size*/

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he; /* host info */
    struct sockaddr_in their_addr; /* peer addr */
    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

     /* get the host info */
    if ((he=gethostbyname(argv[1])) == NULL) {
    /* notice: to acquire DNS，erroe msg express herror not by perror */
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT); /* short, NBO */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8); /* reset other data with 0 */
    
    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);  
    }
    
    if ((numbytes=recv(sockfd,buf,MAXDATASIZE,0))==-1) {
        perror("recv");
        exit(1); 
    }
    
    buf[numbytes] = '\0';
    printf("Received: %s",buf); 
    close(sockfd);
    
    return 0;
}
