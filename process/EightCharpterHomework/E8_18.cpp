#include "csapp.h"
void end(void){
    printf("2--which process:%d\n",getpid());
}
int main(){
    if(fork()==0)
        atexit(end);
    if(fork()==0)
        printf("0--which process:%d\n",getpid());
    else
    {
        printf("1--which process:%d\n",getpid());
    
    }
    exit(0);
}