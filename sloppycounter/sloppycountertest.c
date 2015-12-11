#include <stdio.h>
#include <stdlib.h>
#include "sloppycounter.c"
#include "../gettime/gettime.c"
#define TIME 1000000
//#define THRESHOLD 10000
#define PNUM 40

typedef struct __mi
{
    counter_t c;
    int tid;
}mi;

int main()
{
    void *pf(mi *m);
    pthread_t p[PNUM];
    counter_t c;
    counter_init(&c,THRESHOLD, 0);
    mi m;
    m.c = c;
    int i;
    double a,b;
    a = gettime(0);
    for(i=0;i<PNUM;i++)
    {
        m.tid = PNUM % NUMCPUS;
        pthread_create(&p[i], NULL, pf, &m);
    }
    for(i=0;i<PNUM;i++)
    {
        pthread_join(p[i], NULL);
    }
    b = gettime(1);
    printf("time = %lf s\n",b-a);
    printf("lock : %d\n", counter_get(&m.c));
    return 0;
}

void *pf(mi *m)
{
    int i;
    for(i=0;i<TIME;i++)
    {
        counter_update(&m -> c, m -> tid , 1);
    }
}
