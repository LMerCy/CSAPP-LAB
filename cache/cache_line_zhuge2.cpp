#include<cstdio>
#include<cstdlib>
#include<ctime>
int main(){
    static constexpr int len = 64*1024*1024;
    int* arr = (int*)malloc(sizeof(int)*len);
    for(int i=0;i<len;++i)
        arr[i] =1;
    //clock_t loop2_start =clock();
    for(int i=0;i<len;i+=1024)
        arr[i] *= 3;
    //clock_t loop2_end = clock();
   //printf("arrarysize: %d  loop2 satrt : %lu end: %lu elapsed: %f\n",len/1024*4,loop2_start,loop2_end, ((double)loop2_end-loop2_start)/CLOCKS_PER_SEC);
    
    return 0;
}