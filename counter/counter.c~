#include "counter.h"

void counter_init(counter_t *c, int value)
{
    c -> value = value;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_init(&c -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_init(&c -> lock);
    #else
        pthread_mutex_init(&c -> lock, NULL);
    #endif
}

int counter_get_value(counter_t *c)// inaccurate version.
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&c -> lock);
        int r = c -> value;
        spinlock_release(&c -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&c -> lock);
        int r = c -> value;
        mutex_release(&c -> lock);
    #else
        pthread_mutex_lock(&c -> lock);
        int r = c -> value;
        pthread_mutex_unlock(&c -> lock);
    #endif
    return r;
}

void counter_increment(counter_t *c)
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&c -> lock);
        c -> value++;
        spinlock_release(&c -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&c -> lock);
        c -> value++;
        mutex_release(&c -> lock);
    #else
        pthread_mutex_lock(&c -> lock);
        c -> value++;
        pthread_mutex_unlock(&c -> lock);
    #endif
}

void counter_decrement(counter_t *c)
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&c -> lock);
        c -> value--;
        spinlock_release(&c -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&c -> lock);
        c -> value--;
        mutex_release(&c -> lock);
    #else
        pthread_mutex_lock(&c -> lock);
        c -> value--;
        pthread_mutex_unlock(&c -> lock);
    #endif
}

