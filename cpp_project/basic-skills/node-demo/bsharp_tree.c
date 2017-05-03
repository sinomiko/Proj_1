/*************************************************************************
	> File Name: bsharp_tree.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Thu 15 Dec 2016 05:35:57 PM PST
 ************************************************************************/

#include<stdio.h>
#include <malloc.h>
typedef struct PayloadSession {
    int payload_idx;
}PayloadSession;

struct BNodeKey {
    void     *engine;    //related RPS engine
};

typedef struct PayloadSessionPool{
    PayloadSession *sessions;
}PayloadSessionPool;

PayloadSessionPool* g_PayloadSessionPool;
void ginitializer()
{
    g_PayloadSessionPool=(PayloadSessionPool*)malloc(sizeof(PayloadSessionPool));
}


void changePayloadSession(PayloadSession* psession)
{
     g_PayloadSessionPool->sessions=psession;
   
}

void showPayloadSession()
{
     printf("payload_idx: %d \n",g_PayloadSessionPool->sessions->payload_idx);
}

void main(void)
{
    ginitializer(); 
    PayloadSession * psession=(PayloadSession *)malloc(sizeof(PayloadSession));
    if (psession!=NULL)
        {
            psession->payload_idx=1;
        }
    changePayloadSession(psession);
    showPayloadSession();
    psession->payload_idx=2;
    changePayloadSession(psession);
    showPayloadSession();
    
}
