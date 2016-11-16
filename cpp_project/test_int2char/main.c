/*************************************************************************
	> File Name: main.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 15 Nov 2016 06:27:30 PM PST
 ************************************************************************/
#include <string.h>
#include<stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
 
struct pkt_key_ipv4_5tuple {
    uint8_t ttl;
    uint8_t proto;
    uint16_t checksum;
    uint32_t ip_src;
    uint32_t ip_dst;
    uint16_t port_src;
    uint16_t port_dst;
} __attribute__((__packed__));

struct pkt_key_ipv6_5tuple {
    uint16_t payload_length;
    uint8_t proto;
    uint8_t hop_limit;
    uint8_t ip_src[16];
    uint8_t ip_dst[16];
    uint16_t port_src;
    uint16_t port_dst;
} __attribute__((__packed__));

struct pkt_key_ipv6_5tuple test_ipv6;


char* manu_char(char* pchar){
    pchar=(char *)malloc(sizeof(char)*16);
    memcpy ( pchar, "hello", 6 );
    return pchar;
}

char** manu_char2(char** pchar){
    *pchar=(char *)malloc(sizeof(char)*16);
    memcpy ( *pchar, "manu_char2", 6 );
    return pchar;
 }

void main(void){
    int array[10]={0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 10; ++i)
	printf("array: %c \n",array[i]+48);
    for (int i = 0; i < 129; ++i)
    {
	printf("decimal: %d <---> char:%c \n", i,i);
    }

    char* ch1="abcd";
    char* ch2=manu_char(ch1); //first order pointer point to a char* variable address
    printf("ch1 %p: %s\nch2 %p: %s\n",&ch1,ch1,&ch2,ch2);

    char** ch3=manu_char2(&ch1);//second order pointer point to char** variable address
    printf("ch1 %p: %s\nch3 %p: %s\n",&ch1,ch1,&ch3,*ch3);

    char* ipv6="2001:0:0:0:0:0:0:1";
    memcpy (test_ipv6.ip_src, ipv6, strlen(ipv6)+1 );
    printf("test_ipv6.ip_src_len: %d \n",strlen(test_ipv6.ip_src));
    printf("sizeof uint8_t: %d \n",sizeof(uint8_t));
    printf("test_ipv6.ip_src_d: %d \ntest_ipv6.ip_src_s: %s \n",test_ipv6.ip_src,test_ipv6.ip_src);    

}
