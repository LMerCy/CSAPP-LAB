#include "csapp.h"
void *thread(void *vargp);
volatile int cnt = 0;
sem_t mutex;
int main(int argc,char **argv){
    int niters;
    sem_init(&mutex,0,1);
    pthread_t pid1,pid2;
    if(argc != 2){
        printf("not enough para!\n");
        exit(0);
    }
    niters = atoi(argv[1]);
    pthread_create(&pid1,NULL,thread,&niters);
    pthread_create(&pid2,NULL,thread,&niters);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    if(cnt!=2*niters)
        printf("BOOM! cnt = %d\n",cnt);
    else
    {
        printf("OK cnt = %d\n",cnt);
    }
    exit(0);
    
}
void *thread(void *vargp){
    int i;
    int niters = *((int *)vargp);
    for(i =0;i<niters;i++){
        sem_wait(&mutex);
        cnt ++;
        sem_post(&mutex);
    }
    return  NULL;
}