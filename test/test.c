#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "choosestruc.h"
#include "../gettime/gettime.c"

#if CUR_STRUC == COUNTER
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
            pthread_create(&p[i], NULL, (void*)pf, &c);
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
#elif CUR_STRUC == SLOPPY_COUNTER
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
            pthread_create(&p[i], NULL, (void*)pf, &m);
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
#elif CUR_STRUC == LINKLIST
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
            pthread_create(&p[i], NULL, (void*)pf, &c);
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
#else
    int main()
    {
        void *pf(hash_t *c);
        pthread_t p[PNUM];
        hash_t c;
        hash_init(&c,100);
        int i;
        double a,b;
        a = gettime(0);
        for(i=0;i<PNUM;i++)
        {
            pthread_create(&p[i], NULL, (void*)pf, &c);
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
#endif

