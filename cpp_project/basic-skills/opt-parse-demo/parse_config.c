/*************************************************************************
	> File Name: parse_config.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Wed 15 Mar 2017 12:20:44 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>


#define LONG_OPT_PID_FILE     "pid-file"
#define LONG_OPT_CONFIG       "config"
#define LONG_OPT_NO_NUMA      "no-numa"
#define LONG_OPT_ENABLE_JUMBO "enable-jumbo"
#define LONG_OPT_MAX_FLOWS    "maxflows"
#define LONG_OPT_FLOW_TTL     "flowttl"
#define LONG_OPT_LOG_SERVER   "log-server"
#define LONG_OPT_OAM_LCORES   "oam-lcores"

struct RxQBinding {
    uint8_t port_id;    /* physical port ID */
    uint8_t queue_id;   /* RX Queue ID */
    uint8_t lcore_id;   /* core ID */

#define MAX_RXQ_BINDING 1024
}; 
struct RxQBinding s_rx_bindings[MAX_RXQ_BINDING];
struct RxQBinding s_rx_bindings_default[] = {
    {0, 0, 2},
    {0, 1, 2},
    {0, 2, 2},
    {1, 0, 2},
    {1, 1, 2},
    {1, 2, 2},
    {2, 0, 2},
    {3, 0, 3},
    {3, 1, 3},
};

struct RxQBinding * g_rx_bindings = s_rx_bindings_default;
uint16_t g_num_bindings = sizeof(s_rx_bindings_default) /
    sizeof(s_rx_bindings_default[0]);

#define MAX_SIZE 1000
//int split_up(char* string, char* argv[])
//{
//    char* p = string;
//    int argc = 0;
//
//    while(*p != ',')
//    {
//        while(isspace(*p))
//            ++p;
//
//        if(*p != ',')
//            argv[argc++] = p;
//        else
//            break;
//
//        while(*p != ',' && !isspace(*p))
//            p++;
//        if(*p != ',')
//        {
//            *p = ',';
//            ++p;
//        }
//
//    }
//
//    return argc;
//}
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

/** parse (portid, queueid, lcoreid) bindings */
static int parse_config(const char *q_arg)
{
    char s[256];
    const char *p, *p0 = q_arg;
    char *end;
    enum fieldnames {
        FLD_PORT = 0,
        FLD_QUEUE,
        FLD_LCORE,
        _NUM_FLD
    };
    unsigned long int_fld[_NUM_FLD];
    char *str_fld[_NUM_FLD];
    int i;
    unsigned size;

    g_num_bindings = 0;

    while ((p = strchr(p0,'(')) != NULL) {
        ++p;
        if((p0 = strchr(p,')')) == NULL)
            return -1;

        size = p0 - p;
        if(size >= sizeof(s))
            return -1;

        snprintf(s, sizeof(s), "%.*s", size, p);
        printf("% s\n",s);
       // if (strsplit(s, sizeof(s), str_fld, _NUM_FLD, ',') != _NUM_FLD)
         //   return -1; 
        split_up(s, str_fld);
        printf("% s\n",str_fld[0]); 
        for (i = 0; i < _NUM_FLD; i++){
            errno = 0;
            int_fld[i] = strtoul(str_fld[i], &end, 0);
            if (errno != 0 || end == str_fld[i] || int_fld[i] > 255)
                return -1;
        }
        if (g_num_bindings >= MAX_RXQ_BINDING) {
            printf("exceeded max number of lcore params: %hu\n", g_num_bindings);
            return -1;
        }
        s_rx_bindings[g_num_bindings].port_id = (uint8_t)int_fld[FLD_PORT];
        s_rx_bindings[g_num_bindings].queue_id = (uint8_t)int_fld[FLD_QUEUE];
        s_rx_bindings[g_num_bindings].lcore_id = (uint8_t)int_fld[FLD_LCORE];
        ++g_num_bindings;
    }
    g_rx_bindings = s_rx_bindings;
    return 0;
}


int main(int argc, char **argv)
{
    int opt, ret;
    char **argvopt;
    int optidx;
    char *prgname = argv[0];
    bool set_portmask = false;
    bool set_lttid = false;
    bool set_pidfile = false;
    bool set_config = false;
    static struct option lgopts[] = {
        {LONG_OPT_PID_FILE    , 1, 0, 0},
        {LONG_OPT_CONFIG      , 1, 0, 0},
        {LONG_OPT_NO_NUMA     , 0, 0, 0},
        {LONG_OPT_ENABLE_JUMBO, 0, 0, 0},
        {LONG_OPT_MAX_FLOWS   , 1, 0, 0},
        {LONG_OPT_FLOW_TTL    , 1, 0, 0},
        {LONG_OPT_LOG_SERVER  , 1, 0, 0},
        {LONG_OPT_OAM_LCORES  , 1, 0, 0},
        {NULL, 0, 0, 0}
    };

    argvopt = argv;
    while ((opt = getopt_long(argc, argvopt, "p:P:i:", lgopts, &optidx)) != EOF) {
        switch (opt) {
            /* portmask */
           case 'p': 
           case 'P':
           case 'i':
                break ; 
           case 0:
                   printf("before\n");
                  if (!strncmp(lgopts[optidx].name, LONG_OPT_CONFIG,
                            sizeof (LONG_OPT_CONFIG))) {
                    if (parse_config(optarg) < 0) {
                        printf("invalid value: \"%s\" for parameter %s\n",
                                optarg, lgopts[optidx].name);
                        goto error;
                    }
                    set_config = true;
           default:
                   goto error;
                }
        }
   }
error:
  printf("it is over");
}

