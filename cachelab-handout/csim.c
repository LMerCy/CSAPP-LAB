#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
void helpinfo(){
    printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    exit(1);
}

int main(int argc,char **argv)
{
    int optg,s = 0,E = 0,b = 0, trace = 0;
    char *filepath;
    while((optg = getopt(argc,argv,"hvs:E:b:t:"))!=-1){
        switch (optg)
        {
        case 'h':
            /* code */
            helpinfo();
            break;
        case 'v':
            break;
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace = 1;
            filepath = optarg;
            break;
        default:
            helpinfo();
            break;
        }
    }
    printf(" s:%d,E:%d,b:%d\n",s,E,b);
    if(s == 0 | E == 0| b == 0| trace == 0){
        printf("param value cannt be 0 !\n");
        helpinfo();
    }
    printSummary(0, 0, 0);
    return 0;
}
