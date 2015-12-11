#ifndef SLOPPYCOUNTER_H_INCLUDED
#define SLOPPYCOUNTER_H_INCLUDED

#include "../locks/chooselock.h"

#if CUR_MUTEX == MUTEX2
    #include "../locks/mutex2.c"
#elif CUR_MUTEX == MUTEX3
    #include "../locks/mutex3.c"
#else
    #include "../locks/mutex4.c"
#endif

#include "../locks/spinlock.c"
#define NUMCPUS 4
#define THRESHOLD 100000

typedef struct __counter_t_
{
    int global;
    int threshold;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_t glock;
        spinlock_t llock[NUMCPUS];
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_t glock;
        mutex_t llock[NUMCPUS];
    #else
        pthread_mutex_t glock;
        pthread_mutex_t llock[NUMCPUS];
    #endif
    int local[NUMCPUS];
}counter_t;

void counter_init(counter_t *c, int threshold, int value);
void counter_update(counter_t *c, int threadID, int amt);
int counter_get(counter_t *c);

#endif // SLOPPYCOUNTER_H_INCLUDED
