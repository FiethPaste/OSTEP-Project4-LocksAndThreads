#include "chooselock.h"

typedef struct __mutex_t
{
    int flag;
    int queue;
}mutex_t;

void increment(mutex_t *mutex)
{
    mutex -> queue ++;
}

void decrement(mutex_t *mutex)
{
    mutex -> queue --;
}

void mutex_init(mutex_t *mutex)
{
    mutex -> flag = 0;
    mutex -> queue = 0;
}

void mutex_acquire(mutex_t *mutex)
{
    int v;
    if(xchg(&mutex -> flag, 1) == 0)
    {
        return;
    }
    increment(mutex);
    while(1)
    {
        if(xchg(&mutex -> flag, 1) == 0)
        {
            decrement(mutex);
            return;
        }
        v = mutex -> queue;
        //xchg(&v, mutex -> queue);
        if(v == 0) continue;
        sys_futex (&mutex -> queue, FUTEX_WAIT, v, 0, 0, 0);
    }
}

void mutex_release(mutex_t *mutex)
{
    /*if(mutex -> queue == 0)
    {
        mutex ->flag = 0;
        return;
    }*/
    xchg(&mutex ->flag ,0);
    sys_futex(&mutex -> queue, FUTEX_WAKE, 1, 0, 0, 0);
}
