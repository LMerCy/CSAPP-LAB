#include "csapp.h"
#define M 1000
#define N 1000
#define MAXTHREADS 32

long ncol_per_threads;
int A[M][N];
int B[N][M];
int C[M][M];
void initMatrix(int A[M][N], int B[N][M]) //m=a n=b
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            // A[i][j] = i+j;  /* The matrix created this way is symmetric */
            A[i][j]=rand();
            B[j][i]=rand();
        }
    }
}

void randMatrix( int A[M][N]) {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
            // A[i][j] = i+j;  /* The matrix created this way is symmetric */
            A[i][j]=rand();
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
            for(int k=0;k<N;k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}
void parallelMul(int nthreads){
    pthread_t tid[MAXTHREADS];
    int myid[MAXTHREADS];
    ncol_per_threads = M/nthreads;

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
    initMatrix(A,B);
    parallelMul(atoi(argv[1]));
    return 0;
}