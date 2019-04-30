#include "csapp.h"
#define MAXBUF 8192
void handler(int sig){
    pid_t pid;
    while((pid = waitpid(-1,NULL,0))>0){
        printf("handler reaped child %d\n",(int)pid);
    }
    if( errno!= ECHILD)
    {
        unix_error("waitpid error");
    }
    
    sleep(2);
    return ;
}
int main(){
    pid_t pid;
    int n;
    char buf[MAXBUF];
    if(signal(SIGCHLD,handler) == SIG_ERR){
        printf("signal error");
        exit(0);
    }
    for(int i  = 0;i<3;i++){
        if(fork()==0){
            printf("hello from child %d\n",(int)getpid());
            sleep(1);
            exit(0);
        }
    }
    if((n = read(STDIN_FILENO,buf,sizeof(buf)))<0){
        unix_error("read error");
    }
    printf(" parent processing input \n");
    while(1){

    }
    exit(0);
}