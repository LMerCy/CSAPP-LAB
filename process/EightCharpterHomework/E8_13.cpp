#include "csapp.h"
int main(){
    int x =3;
    if(fork()!=0)
        printf("x=%d\n",++x);
    printf("x=%d\n",--x);
    waitpid(-1,NULL,0);
    exit(0);
}