#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
typedef struct{
    unsigned int sig;
    unsigned int valid;
    unsigned int accesstime;
}Cacheline;
typedef struct{
    Cacheline *cl;
}Set;
typedef struct{
    unsigned long int nSet;
    unsigned long int nCacheline;
    Set * set;
}Cache;
typedef struct{
    char type;
    unsigned int address;
    unsigned int setindex;
    unsigned long int sig;
    unsigned int memsize;
}Operation;
typedef struct{
    bool hit;
    bool eviction;
}hitrestult;
int miss =0 ,hit = 0,eviction = 0;
unsigned int accesstimes = 0;
void helpinfo(){
    printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    exit(1);
}
void updateaccessime(Cacheline *cl){
    cl->accesstime =accesstimes;
}
void updatecacheline(Operation op,Cacheline *cl){
    cl->sig = op.sig;
    cl->valid = 1;
    updateaccessime(cl);
}
// void lru(Operation op,Cache *cache,hitrestult *hr){
//     unsigned int least = 0;
//     Cacheline * lruCacheline;
//     for(int  i=0;i<(cache -> nSet);i++){
//         for(int j=0;j<(cache->nCacheline);j++){
//             if(cache->set[i].cl[j].accesstime < least){
//                 lruCacheline = &(cache->set[i].cl[j]);
//                 least = cache->set[i].cl[j].accesstime;
//             }
//         }

//     }
//     if(least > 0){
//         hr->eviction = true;
//         eviction++;
//     }
        
//     updatecacheline(op,lruCacheline);
// }
void lru(Operation op,Cache *cache,unsigned long int setindex,hitrestult *hr){
    unsigned long int least =cache->set[setindex].cl[0].accesstime;
    Cacheline * lruCacheline;
    bool hasEmptyline = false;
    for(int i=0;i<(cache->nCacheline);i++){
        //查看是否有空行，若有立即替换，若无，再记录是否覆盖
        if(cache->set[setindex].cl[i].valid == 0){
            hasEmptyline = true;
            lruCacheline = &(cache->set[setindex].cl[i]);
            break;
        }
        if(cache->set[setindex].cl[i].accesstime <= least){
            lruCacheline = &(cache->set[setindex].cl[i]);
            least = cache->set[setindex].cl[i].accesstime;
        }
    }
    if(!hasEmptyline){
        hr->eviction = true;
        eviction++;
    }
        
    updatecacheline(op,lruCacheline);
}


void initcache(int s,int E,int b,Cache * cache){
    cache->nSet = 1L <<s;
    cache->nCacheline = E;
    cache->set = (Set *)malloc(cache->nSet * sizeof(cache));
    for(int i=0;i< cache->nSet;i++){
        cache->set[i].cl = (Cacheline *)malloc(cache->nCacheline * sizeof(Cacheline));
        for(int j=0;j< cache->nCacheline;j++){
            cache->set[i].cl[j].valid = 0;
            cache->set[i].cl[j].sig = 0;
            cache->set[i].cl[j].accesstime = 0;
        }
    }
}
void caching(Operation op, Cache *cache, hitrestult *hr){
    //  if op.sig in cache[op.setindex] hit!
    //  else miss then lru

    accesstimes ++;

    for(int i=0;i<(cache->nCacheline);i++){
        if(cache -> set[op.setindex].cl[i].sig == op.sig){
            if(cache -> set[op.setindex].cl[i].valid){
                hr->hit = true;
                updatecacheline(op,&(cache -> set[op.setindex].cl[i]));
                hit++;
            }
                
        }
    }
    if(!(hr->hit)){
        //首先查看该组内是否有空的缓存行（有效值==0），若有直接放入，若无采用lru。
        //LRU 替换最新的 并且若发生了替换需要将eviction置为真。
        //首先找到最早被使用的 cacheline 替换掉！ 
        miss ++;
        
        lru(op,cache,op.setindex,hr);
        
    }
    return ;
    

}
int main(int argc,char **argv)
{
    int optg,s = 0,E = 0,b = 0, trace = 0,verbose = 0;
    char *filepath;
    Cache simCache;
    FILE *tracefile;
    Operation op;
    char opchar[100];
    char *ptropchar;
    hitrestult hr;
    unsigned long int opaddressbak;
    while((optg = getopt(argc,argv,"hvs:E:b:t:"))!=-1){
        switch (optg)
        {
        case 'h':
            /* code */
            helpinfo();
            break;
        case 'v':
            verbose = 1;
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
    if(s == 0 || E == 0 || b == 0 || trace == 0){
        printf("param value cannt be 0 !\n");
        helpinfo();
    }
    initcache(s,E,b,&simCache);
    tracefile = fopen(filepath,"r");
    while(fgets(opchar,100,tracefile)!=NULL){
        ptropchar = opchar;
        ptropchar[strlen(opchar)-1] = 0;
        if(*ptropchar++ == 'I')
            continue;
        hr.hit = false;
        hr.eviction = false;
        sscanf(ptropchar,"%s %x %d",&op.type,&op.address,&op.memsize);
        opaddressbak = op.address;
        op.setindex = (op.address >> b) &((1L << s) -1);
        op.sig = (opaddressbak >> (b+s));
        caching(op, &simCache, &hr);
        if(verbose){
            printf("%s %s",ptropchar,hr.hit? "hit":"miss");
            if(hr.eviction)
                printf(" eviction");
        }
        if(op.type == 'M'){
            caching(op, &simCache, &hr);
            if(verbose){
                printf(" hit");
            }
        }
        if(verbose)
            printf("\n");
            
    }
    
    
    printSummary(hit, miss, eviction);
    return 0;
}
