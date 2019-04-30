#include "csapp.h"
void mmacopy(int fd,int size){
    char *bufp;
    mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);
    write(1,bufp,size);
    return;
}
int main(int argc,char ** argv){
    struct stat stat;
    
    if(argc != 2)
        printf("not enough para!\n");
    char *filename = argv[1];
    int rc = open(filename,O_RDONLY,0);
    if(rc<0)
        unix_error("open error!\n");
    fstat(rc,&stat);
    printf("rc:%d\n",rc);
    mmacopy(rc,stat.st_size);
    return 0;
}