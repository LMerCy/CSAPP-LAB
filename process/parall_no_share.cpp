#include "csapp.h"
int count = 2;
pid_t pid;
void handler(int sig){
    count--;
    printf("%d",count);
    fflush(stdout);
    //exit(0);
}
int main(){
    signal(SIGUSR1,handler);
    printf("%d",count);
    fflush(stdout);
    if((pid = fork())==0){
        while(1){

        }
    }
    kill(pid,SIGUSR1);
    waitpid(-1,NULL,0);
    count ++;
    printf("%d",count);
    exit(0);
}