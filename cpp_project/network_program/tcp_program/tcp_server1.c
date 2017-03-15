/*************************************************************************
	> File Name: tcp_server1.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 14 Mar 2017 10:33:39 PM PDT
 ************************************************************************/

  
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT  7770                 /* listen port */
#define BACKLOG 10                 /* listen num */

void main() 
{

    int sockfd, new_fd;             /* fD，data port */
    struct sockaddr_in sa;         /* self addr */
    struct sockaddr_in their_addr; /* peer addr */
    int sin_size;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(MYPORT);        
    sa.sin_addr.s_addr = INADDR_ANY;     /* local IP */
    bzero(&(sa.sin_zero), 8);             /* reset all with 0 */

    if (bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {       
        perror("listen");      
        exit(1);        
    }

    /* main loop */  
    while(1) {  
        sin_size = sizeof(struct sockaddr_in);       
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);     
        if (new_fd == -1) {      
            perror("accept");      
            continue;  
        }
        //printf("Got connection from  %s \n", inet_ntoa(their_addr.sin_addr));

        if (fork() == 0) {
	
            /* son thread */  
	    
            if (send(new_fd, "Hello, world!\n", 14, 0) == -1)        
                perror("send");
		
            close(new_fd);        
            exit(0);

        }

        close(new_fd);
	
    /*kill all fork thread */
    while(waitpid(-1,NULL,WNOHANG) > 0);

    }
}
