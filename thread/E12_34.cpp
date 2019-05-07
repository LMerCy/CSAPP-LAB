#include "csapp.h"
#define N 4
#define L 4
#define M 4
#define MAXTHREADS 32
long ncol_per_threads;
int A[N][L]={{5,1,2,3},{5,1,2,4},{5,1,2,1},{2,3,3,7}};
int B[L][N] = {{35,31,73,94},{15,22,13,47},{53,41,2,1},{22,32,13,7}};
int C[N][N];
void nonParallel(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            int sum =0;
            for(int k=0;k<L;k++){
                sum += A[i][k]*B[k][j];
            }
            C[i][j] = sum;
        }   
    }
}
void *thread(void *vargp){
    int id = *((int *)vargp);
    long start = id * ncol_per_threads;
    long end = (id+1)*ncol_per_threads;
    for(int i=start;i<end;i++){
        for(int j=0;j<M;j++){
            int sum = 0;
            for(int k=0;k<L;k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}
void parallelMul(int nthreads){
    pthread_t tid[MAXTHREADS];
    int myid[MAXTHREADS];
    ncol_per_threads = N/nthreads;

    for(int i=0;i<nthreads;i++){
        myid[i] = i;
        pthread_create(&tid[i],NULL,thread,&myid[i]);
    }
    for(int i=0;i<nthreads;i++){
        pthread_join(tid[i],NULL);
    }
    return ;
}
int main(int argc,char **argv){
    nonParallel();
    return 0;
}