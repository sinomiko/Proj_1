#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void *thread_function(void *args){
    int i;
    for (i=0;i<20;i++ ){
        printf("thread %d says hi!\n",i);
        sleep(1);
    }
    return NULL;
}

int main(void){
    pthread_t mythread;

    if( pthread_create(&mythread,NULL,thread_function,NULL)){
        printf("error creating thread");
        abort();
    }
    int i;
    for (i=0;i<20;i++){
        printf("mian say %d \n",i); 
        sleep(1);
    }
    if(pthread_join(mythread,NULL)){
        printf("error joining thread");
        abort();
    }
    exit(0);
}
