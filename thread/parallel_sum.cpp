#include "csapp.h"
#define MAXTHREADS 32
void *sum(void *vargp);
long psum[MAXTHREADS];
long nelems_per_thread;
int main(int argc,char ** argv){
    if(argc !=3){
        printf("not enought param!\n");
        exit(0);
    }
    int log_nelems = atoi(argv[1]);
    int nthreads = atoi(argv[2]);
    long result = 0;
    pthread_t tid[MAXTHREADS];
    long nelems =  (1L << log_nelems);
    nelems_per_thread = nelems / nthreads;
    int myid[MAXTHREADS];
    for(int i=0;i<nthreads;i++){
        myid[i] = i;
        pthread_create(&tid[i],NULL,sum,&myid[i]);//why use myid,not i directly? because here is pointer main thread would change it's value. 
    }
    for(int i=0;i<nthreads;i++){
        pthread_join(tid[i],NULL);
    }
    for(int i=0;i<nthreads;i++){
        result += psum[i];
    }
    if(result != (nelems*(nelems-1)/2))
        printf("error: restult = %ld\n",result);
    else
        printf("Correct! result = %ld\n",result);
    exit(0);
}
void *sum(void *vargp){
    int myid = *((int *)vargp);
    printf("myid:%d\n",myid);
    long start = myid*nelems_per_thread;
    long end = (myid+1) * nelems_per_thread;
    long temp_sum = 0;
    for(long i = start;i<end;i++)
        temp_sum += i;
    psum[myid] = temp_sum;
    return NULL;
}