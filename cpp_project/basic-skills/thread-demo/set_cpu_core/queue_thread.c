/*************************************************************************
	> File Name: queue_thread.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Sun 14 May 2017 10:46:55 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define QUEUE_LENGTH 10
#define NUM_CHILDREN 5

void perror_exit(char * str){
    perror(str);
    exit(1);
}

typedef pthread_mutex_t Mutex;

typedef pthread_cond_t Cond;

typedef struct{
    int *array;
    int length;
    int next_in;
    int next_out;
    Mutex *mutex;
    Cond *nonempty;
    Cond *nonfull;
} Queue;

typedef struct {
    Queue *queue;
} Shared;

void *check_malloc(int size){
    void *p = malloc(size);
    if(p == NULL){
        perror("malloc failed");
        exit(1);
    }
    return p;
}

Cond *make_cond(){
    Cond *cond = check_malloc(sizeof(Cond));
    int n = pthread_cond_init(cond, NULL);
    if (n != 0) perror_exit("make_cond failed");
    return cond;
}

void cond_wait(Cond *cond, Mutex *mutex){
    int n = pthread_cond_wait(cond, mutex);
    if (n != 0) perror_exit("cond_wait failed");
}

void cond_signal(Cond *cond){
    int n = pthread_cond_signal(cond);
    if (n != 0) perror_exit("cond_signal failed");
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

Queue *make_queue(int length){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->length = length;
    queue->array = (int *) malloc( length *sizeof(int));
    queue->next_in = 0;
    queue->next_out = 0;
    queue->mutex = make_mutex();
    queue->nonempty = make_cond();
    queue->nonfull = make_cond();
    return queue;
}

Shared *make_shared(){
    Shared *shared = check_malloc(sizeof(Shared));
    shared->queue = make_queue(QUEUE_LENGTH);
    return shared;
}

int queue_empty(Queue *queue)
{
    return (queue->next_in == queue->next_out);
}

void queue_push(Queue *queue, int item){
    mutex_lock(queue->mutex);
//    if (queue_full(queue)) {
//        mutex_unlock(queue->mutex);
//        perror_exit("queue is full");
//    }
    while (queue_full(queue)) {
        cond_wait(queue->nonfull, queue->mutex);
    }

    queue->array[queue->next_in] = item;
    queue->next_in = queue_incr(queue, queue->next_in);
    mutex_unlock(queue->mutex);
    cond_signal(queue->nonempty);
}

int queue_incr(Queue *queue, int value){
    return (value+1)%(queue->length);
}

int queue_full(Queue *queue)
{
    return (queue_incr(queue,queue->next_in)==queue->next_out);
}

int queue_pop(Queue *queue){
    mutex_lock(queue->mutex);
//    if(queue_empty(queue)){
//        mutex_unlock(queue->mutex);
//        perror_exit("queue is empty");
//    }

    while (queue_empty(queue)) {
        cond_wait(queue->nonempty, queue->mutex);
    }

    int item = queue->array[queue->next_out];
    queue->next_out = queue_incr(queue, queue->next_out);
    mutex_unlock(queue->mutex);

    cond_signal(queue->nonfull);

    return item;
}

void *producer_entry(void *arg){
    int i;
    Shared *shared = (Shared*) arg;

    for(i=0; i<QUEUE_LENGTH-1; i++){
        printf("adding item %d \n", i);
        queue_push(shared->queue, i);
    }
    pthread_exit(NULL);
}

void *consumer_entry(void *arg){
    int i;
    int item;
    Shared *shared = (Shared*) arg;

    for(i=0; i<QUEUE_LENGTH-1; i++){
        item = queue_pop(shared->queue);
        printf("consuming item %d \n", item);
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

int main(void){
    int i;
    pthread_t child[NUM_CHILDREN];
    Shared *shared = make_shared();
    child[0] = make_thread(producer_entry, shared);
    child[1] = make_thread(consumer_entry, shared);
    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }
    return 0;
}
