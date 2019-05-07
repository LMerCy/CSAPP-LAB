#include "csapp.h"
#define N 20
#define L 20
#define M 20
#define MAXTHREADS 32
long ncol_per_threads;
int A[N][L]={{5,1,2,3,2,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{5,1,2,4,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{5,1,2,1,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{2,3,3,7,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{2,3,3,7,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},
              {2,3,23,7,5,1,21,3,2,2,3,23,7,5,1,21,3,2},{2,33,3,7,5,13,2,3,2,2,3,23,7,5,1,21,3,2},{2,3,3,47,5,1,22,3,2,2,3,23,7,5,1,21,3,2},{22,3,3,7,5,156,2,3,2,2,3,23,7,5,1,21,3,2},{2,3,13,7,5,1,2,33,2,2,3,23,7,5,1,21,3,2},
              {5,1,2,3,2,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{5,1,2,4,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{5,1,2,1,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{2,3,3,7,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},{2,3,3,7,5,1,2,3,2,5,1,2,3,2,5,1,2,3,2},
              {2,3,23,7,5,1,21,3,2,2,3,23,7,5,1,21,3,2},{2,33,3,7,5,13,2,3,2,2,3,23,7,5,1,21,3,2},{2,3,3,47,5,1,22,3,2,2,3,23,7,5,1,21,3,2},{22,3,3,7,5,156,2,3,2,2,3,23,7,5,1,21,3,2},{2,3,13,7,5,1,2,33,2,2,3,23,7,5,1,21,3,2}};

int B[L][N] = {{52,1,2,33,2,5,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{5,14,2,4,55,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{56,1,2,1,35,1,72,3,2,52,1,2,33,2,5,1,2,3,2},{2,3,3,7,25,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{2,3,34,7,5,12,2,3,2,52,1,2,33,2,5,1,2,3,2},
              {2,3,23,17,5,1,221,3,2,2,3,23,17,5,1,221,3,2},{2,33,233,7,5,13,2,3,2423,2,3,23,17,5,1,221,3,2},{2,3,3,47,5,121,22,3,2,2,3,23,17,5,1,221,3,2},{322,3,3,74,5,156,2,33,2,2,3,23,17,5,1,221,3,2},{2,3,13,17,5,1,212,332,2,2,3,23,17,5,1,221,3,2},
              {52,1,2,33,2,5,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{5,14,2,4,55,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{56,1,2,1,35,1,72,3,2,52,1,2,33,2,5,1,2,3,2},{2,3,3,7,25,1,2,3,2,52,1,2,33,2,5,1,2,3,2},{2,3,34,7,5,12,2,3,2,52,1,2,33,2,5,1,2,3,2},
              {2,3,23,17,5,1,221,3,2,2,3,23,17,5,1,221,3,2},{2,33,233,7,5,13,2,3,2423,2,3,23,17,5,1,221,3,2},{2,3,3,47,5,121,22,3,2,2,3,23,17,5,1,221,3,2},{322,3,3,74,5,156,2,33,2,2,3,23,17,5,1,221,3,2},{2,3,13,17,5,1,212,332,2,2,3,23,17,5,1,221,3,2}};
int C[N][N];
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
    if(argc!=2){
        printf("need 1 params!\n");
        exit(0);
    }
    parallelMul(atoi(argv[1]));
    return 0;
}