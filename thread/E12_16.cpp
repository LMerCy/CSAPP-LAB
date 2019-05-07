#include "csapp.h"
#define MAXTHREADS 32
void *thread(void *vargp);
int main(int argc,char ** argv){
    if(argc!=2){
        printf("not enough params!\n");
        exit(0);
    }
    int nthreads = atoi(argv[1]);
    pthread_t tid[MAXTHREADS];
    int myid[MAXTHREADS];
    for(int i=0;i<nthreads;i++){
        myid[i]=i;
        pthread_create(&tid[i],NULL,thread,&myid[i]);
    }
    for(int i=0;i<nthreads;i++){
        pthread_join(tid[i],NULL);
    }
    exit(0);
}
void *thread(void *vargp){
    int id = *((int *)vargp);
    printf("no:%d   helloworld!\n",id);
    return NULL;
}