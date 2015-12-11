#include <stdio.h>
#include <stdlib.h>
#include "linklist.c"
#include "../gettime/gettime.c"
#define TIME 1000000
#define PNUM 20

int main()
{
    void *pf(list_t *c);
    pthread_t p[PNUM];
    list_t c;
    list_init(&c);
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
    printf("number of nodes = %d",displaynumber(&c));
    return 0;
}

void *pf(list_t *c)
{
    int i;
    for(i=0;i<TIME;i++)
    {
        list_insert(c,i);
    }
}
