#include "sloppycounter.h"

void counter_init(counter_t *c, int threshold, int value)
{
    int i;
    c -> global = value;
    c -> threshold = threshold;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_init(&c -> glock);
        for(i = 0; i < NUMCPUS; i++)
        {
            spinlock_init(&c -> llock[i]);
            c -> local[i] = 0;
        }
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_init(&c -> glock);
        for(i = 0; i < NUMCPUS; i++)
        {
            mutex_init(&c -> llock[i]);
            c -> local[i] = 0;
        }
    #else
        pthread_mutex_init(&c -> glock, NULL);
        for(i = 0; i < NUMCPUS; i++)
        {
            pthread_mutex_init(&c -> llock[i], NULL);
            c -> local[i] = 0;
        }
    #endif
}

void counter_update(counter_t *c, int threadID, int amt)
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&c -> llock[threadID]);
        c -> local[threadID] += amt;
        if(c -> local[threadID] >= c -> threshold)
        {
            spinlock_acquire(&c -> glock);
            c -> global += c -> local[threadID];
            spinlock_release(&c -> glock);
            c -> local[threadID] = 0;
        }
        spinlock_release(&c -> llock[threadID]);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&c -> llock[threadID]);
        c -> local[threadID] += amt;
        if(c -> local[threadID] >= c -> threshold)
        {
            mutex_acquire(&c -> glock);
            c -> global += c -> local[threadID];
            mutex_release(&c -> glock);
            c -> local[threadID] = 0;
        }
        mutex_release(&c -> llock[threadID]);
    #else
        pthread_mutex_lock(&c -> llock[threadID]);
        c -> local[threadID] += amt;
        if(c -> local[threadID] >= c -> threshold)
        {
            pthread_mutex_lock(&c -> glock);
            c -> global += c -> local[threadID];
            pthread_mutex_unlock(&c -> glock);
            c -> local[threadID] = 0;
        }
        pthread_mutex_unlock(&c -> llock[threadID]);
    #endif
}

int counter_get(counter_t *c)// inaccurate
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&c -> glock);
        int r = c -> global;
        spinlock_release(&c -> glock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&c -> glock);
        int r = c -> global;
        mutex_release(&c -> glock);
    #else
        pthread_mutex_lock(&c -> glock);
        int r = c -> global;
        pthread_mutex_unlock(&c -> glock);
    #endif
    return r;
}
