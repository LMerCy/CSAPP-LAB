#include "csapp.h"
int main(){
    pid_t pid;
    int x =1;
    pid =fork();
    if(pid ==0 ){
        printf("child: x=%d\n",++x);
        //exit(0);   //exit(0) only exit its own process
    }
    printf("parent: x=%d\n",--x);
    exit(0);
}
//zhiy