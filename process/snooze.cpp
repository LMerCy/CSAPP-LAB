#include "csapp.h"
void handler(int sig){
    return ;
}
unsigned int snooze(unsigned int secs){
    unsigned int rc = sleep(secs);
    printf("slept for %u of %u secs.\n ",secs-rc,secs);
    return rc;
}
int main(int argc ,char ** argv){
    if(argc<=1){
        printf("arg not enough!");
        return 0;
    }
    int secs = atoi(argv[1]);
    if(signal(SIGINT,handler) == SIG_ERR){
        printf("signal error!\n");
        exit(0);
    }
    snooze(secs);
    exit(0);
}