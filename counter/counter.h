#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED

#include "../locks/chooselock.h"

#if CUR_MUTEX == MUTEX2
    #include "../locks/mutex2.c"
#elif CUR_MUTEX == MUTEX3
    #include "../locks/mutex3.c"
#else
    #include "../locks/mutex4.c"
#endif

#include "../locks/spinlock.c"

typedef struct __counter_t_
{
    int value;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_t lock;
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_t lock;
    #else
        pthread_mutex_t lock;
    #endif
}counter_t;

void counter_init(counter_t *c, int value);
int counter_get_value(counter_t *c);
void counter_increment(counter_t *c);
void counter_decrement(counter_t *c);


#endif // COUNTER_H_INCLUDED
