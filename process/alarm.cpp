#include "csapp.h"
void handler(int sig){
    static int beeps = 0;
    printf("Beep\n");
    if(beeps++<5)
        alarm(1);
    else{
        printf("Boom!\n");
        exit(0);
    }
}
int main(){
    signal(SIGALRM,handler);
    alarm(1);
    while(1){
        ;
    }
    
}