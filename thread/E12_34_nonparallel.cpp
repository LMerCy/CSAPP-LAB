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
void nonParallel(){
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            int sum =0;
            for(int k=0;k<N;k++){
                sum += A[i][k]*B[k][j];
            }
            C[i][j] = sum;
        }   
    }
}

int main(int argc,char **argv){
    nonParallel();
    return 0;
}