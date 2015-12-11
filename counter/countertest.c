#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "counter.c"
#include "../gettime/gettime.c"
#define TIME 1000000
#define PNUM 20

int main()
{
    void *pf(counter_t *c);
    pthread_t p[PNUM];
    counter_t c;
    counter_init(&c,0);
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
    printf("lock : %d\n", c.value);
    return 0;
}

void *pf(counter_t *c)
{
    int i;
    for(i=0;i<TIME;i++)
    {
        counter_increment(c);
    }
}
