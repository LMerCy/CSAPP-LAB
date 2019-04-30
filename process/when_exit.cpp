#include "csapp.h"
void childprocess(int num){
    pid_t pid;
    printf("process num:%d  my pid is :%d\n",num,pid);
} 
int main(){
    for(int i=0;i<5;i++){
        childprocess(i);
        _exit(3);
    }
    exit(0);
}