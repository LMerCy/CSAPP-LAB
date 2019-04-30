#include "csapp.h"
int main(){
    int status;
    pid_t pid;
    printf("helllo\n");
    pid = fork();
    printf("%d\n",!pid);
    if(pid!= 0){
        if(waitpid(-1,&status,0)>0){
            if(WIFEXITED(status)!=0)
            printf("%d\n",WEXITSTATUS(status));
        }
    }
    printf("bye!\n");
    exit(2);
}