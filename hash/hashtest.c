#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "hash.c"
#include "../gettime/gettime.c"
#define TIME 1000000
#define PNUM 20

int main()
{
    void *pf(hash_t *c);
    pthread_t p[PNUM];
    hash_t c;
    hash_init(&c,10);
    int i;
    double a,b;
    a = gettime(0);
    for(i=0;i<PNUM;i++)
    {
        pthread_create(&p[i], NULL, pf, &c);
    }
    for(i=0;i<PNUM;i++)
    {
        pthread_join(p[i], NULL);
    }
    b = gettime(1);
    printf("time = %lf s\n",b-a);
    for(i = 0;i < c.buckets;i ++)
    {
        printf("bucket = %d, nodes = %d\n", i, *(hashdisplay(&c)+i));
    }
    return 0;
}

void *pf(hash_t *c)
{
    int i;
    for(i=0;i<TIME;i++)
    {
        hash_insert(c,i);
    }
}
