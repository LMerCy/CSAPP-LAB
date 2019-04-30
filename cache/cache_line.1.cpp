#include "stdio.h"
#include <stdlib.h>
#include "time.h"
int main(int argc, const char *argv[]){
    int len = atoi(argv[1]);
    const int arrlength = len*1024;
    int arr[arrlength];
    for(int i=0;i<arrlength;i++)
        arr[i] = 1;
    // clock_t loop2_start = clock();
    // for(int i=0;i<arrlength;i+=16)
    //     arr[i] *=3;
    // clock_t loop2_end = clock();
    // printf("loop2 start: %lu  end: %lu  elapsed: %lu\n",loop2_start,loop2_end,loop2_end-loop2_start);
    
    clock_t loop1_start =clock();
    for(int i=0;i<arrlength;i++)
        arr[i] *= 3;
    clock_t loop1_end = clock();
    printf("arrarysize: %d  loop1 satrt : %lu end: %lu elapsed: %lu\n",arrlength/1024*4,loop1_start,loop1_end, loop1_end-loop1_start);
   
    return 0;
}