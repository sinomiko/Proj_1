/*************************************************************************
	> File Name: fsm.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Mon 19 Dec 2016 02:52:12 AM PST
 ************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
typedef enum SessinoState {
    SESSION_IDLE = 0,
    SESSION_RUNNING,
    SESSION_DONE,
    SESSION_STATUS_MAX
}SessinoState;

typedef struct PayloadSession {
    uint32_t idx;
    SessinoState  status;

}PayloadSession;

typedef int (*FsmStateHandler)(PayloadSession* session, uint32_t );


static int fsm_idle_handler(struct PayloadSession* session, uint32_t event)
{
    printf("PayloadSession: %d fsm_idle_handler \n",session->idx);
    return 0;
}

static int fsm_running_handler(struct PayloadSession* session, uint32_t event)
{
    printf("PayloadSession: %d fsm_running_handler \n",session->idx);
    return 0;
}


static int fsm_done_handler(struct PayloadSession* session, uint32_t event)
{
     printf("PayloadSession: %d fsm_done_handler \n",session->idx);
     return 0;
}

static FsmStateHandler s_fsm_handlers[SESSION_STATUS_MAX + 1] = {
    fsm_idle_handler,
    fsm_running_handler,
    fsm_done_handler,
    NULL
};


FsmStateHandler fsm_get_handler(uint32_t status)
{
    if (status < SESSION_STATUS_MAX) {
        return s_fsm_handlers[status];
    }

    printf("error in fsm_get_handler \n");
    return NULL;
}

int fsm_to_state(uint32_t event, PayloadSession* session)
{
    return fsm_get_handler(session->status)(session, event);
}

int main(void)
{
    PayloadSession* ps=(PayloadSession*)malloc(sizeof(PayloadSession));
    ps->idx=123456;
    int i;
    for(i=0; i<1000;i++)
        {
            ps->status=(SessinoState)(i%(SESSION_STATUS_MAX));
            uint32_t event=(uint32_t)i;
            printf("event:%d \n",event);
            fsm_to_state(event,ps);
            sleep(2);
        }
    return 0;
}
