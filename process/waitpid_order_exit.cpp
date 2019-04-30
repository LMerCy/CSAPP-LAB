#include "csapp.h"
int main(){
    int status,i;
    pid_t pid[5],retpid;
    for(i=0;i<5;i++)
        if((pid[i]= fork())==0)
            exit(100+i);
    i=0;
    while((retpid = waitpid(pid[i++],&status,0))>0){
        if(WIFEXITED(status))
            printf("child %d terminated normally with exit status =%d \n",retpid,WEXITSTATUS(status));
        else
        {
            printf("child %d terminated abnormally\n",retpid);
        }
        
    }
    if(errno != ECHILD){
    fprintf(stderr, "%s: %s\n", "waitpid error", strerror(errno));
    exit(0);
    }
    exit(0);
}