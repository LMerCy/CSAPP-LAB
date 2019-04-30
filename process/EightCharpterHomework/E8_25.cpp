#include "csapp.h"
sigjmp_buf env;
void handler(int sig){
    signal(SIGALRM,SIG_DFL);
    siglongjmp(env,1);
}
char * tfgets(char * buf,int buffsize,FILE *stream){
    const unsigned int timesecs = 5;
    signal(SIGALRM,handler);
    alarm(timesecs);
    int rc = sigsetjmp(env,1);
    if(rc == 0) fgets(buf,buffsize,stream);
    else return NULL;
}
int main(int argc,char ** argv){
    char *buf;
    int buffsize = 10;
    tfgets(buf,buffsize,stdin);
    return 0;
}