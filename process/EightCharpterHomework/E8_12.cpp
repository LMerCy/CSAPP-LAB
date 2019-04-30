#include "csapp.h"
void doit(){
    fork();
    fork();
    //printf("hello\n");
    
    return ;
}
int main(){
    //doit();
    fork();
    fork();
    printf("hello\n");
    printf("hello\n");
    exit(0);
}