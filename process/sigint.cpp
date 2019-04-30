#include "csapp.h"
void handler(int sig){
    printf("caught sigint\n");
    exit(0);
}
int main(){
    signal(SIGINT,handler);
    pause();
    exit(0);
}