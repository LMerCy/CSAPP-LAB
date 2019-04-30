#include <stdio.h>
int main(){
    FILE *fp =NULL;
    fp = fopen("/sys/devices/system/cpu/cpu1/cache/index0/size","r");
    char buf[10];
    if(fp!=NULL)
    {
        fgets(buf,10,(FILE*)fp);
        printf("%s\n",buf);
    }
    fclose(fp);
    return 0;
}