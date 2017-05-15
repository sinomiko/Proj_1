/*************************************************************************
	> File Name: main.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Mon 13 Mar 2017 05:59:31 PM PDT
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

typedef pthread_mutex_t Mutex;

typedef struct{
    int counter;
    Mutex *mutex;
}Shared;

void perror_exit(char * str){
    perror(str);
    exit(1);
}

void *check_malloc(int size){
    void *p = malloc(size);
    if(p == NULL){
        perror("malloc failed");
        exit(1);
    }
    return p;
}

Mutex *make_mutex(){
    Mutex *mutex=check_malloc(sizeof(Mutex));
    int n = pthread_mutex_init(mutex,NULL);
    if(n!=0) perror_exit("make_mutex failed");
    return mutex;
}

void mutex_lock(Mutex *mutex){
    int n = pthread_mutex_lock(mutex);
    if(n!=0)perror_exit("mutex_lock failed");
}

void mutex_unlock(Mutex *mutex){
    int n = pthread_mutex_unlock(mutex);
    if(n!=0)perror_exit("mutex_unlock failed");
}

pthread_t make_thread(void*(*entry)(void *), Shared *shared)
{
    int n;
    pthread_t thread;
    n = pthread_create(&thread, NULL, entry, (void *)shared);
    if(n!=0){
        perror("pthread_create failed");
        exit(0);
    }
    return thread;
}

Shared *make_shared(int val){
    Shared *shared = check_malloc(sizeof(Shared));
    shared->counter = val;
    shared->mutex = make_mutex();
    return shared;
}

void child_code(Shared * shared){
    mutex_lock(shared->mutex);
    printf("counter = %d \n", shared->counter);
    shared->counter++;
    mutex_unlock(shared->mutex);
}

void *myfun(void *arg)
{
    cpu_set_t mask;
    cpu_set_t get;
    char buf[256];
    int i;
    int j;
    int num = sysconf(_SC_NPROCESSORS_CONF);
    printf("system has %d processor(s)\n", num);
    for (i = 0; i < num; i++) {
        CPU_ZERO(&mask);
        CPU_SET(i, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
            fprintf(stderr, "set thread affinity failed\n");
        }
        CPU_ZERO(&get);
        if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
            fprintf(stderr, "get thread affinity failed\n");
        }
        for (j = 0; j < num; j++) {
            if (CPU_ISSET(j, &get)) {
                printf("thread %d is running in processor %d\n", (int)pthread_self(), j);
            }
        }
        j = 0;
        while (j++ < 100000000) {
            memset(buf, 0, sizeof(buf));
        }
    }
    pthread_exit(NULL);
}

void join_thread(pthread_t thread){
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror("pthread_join failed");
        exit(-1);
    }
}
#define NUM_CHILDREN 200
void * (*entry)(void*);
int main(int argc, char *argv[])
{
//    pthread_t tid;
//    if (pthread_create(&tid, NULL, (void *)myfun, NULL) != 0) {
//        fprintf(stderr, "thread create failed\n");
//        return -1;
//    }
//    pthread_join(tid, NULL);
    pthread_t child[NUM_CHILDREN];
    Shared *shared = make_shared(1000);

    entry = &child_code;
    int i;
    for(i=0; i<NUM_CHILDREN; i++){
        child[i]=make_thread(entry,shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }
    return 0;
    
}
