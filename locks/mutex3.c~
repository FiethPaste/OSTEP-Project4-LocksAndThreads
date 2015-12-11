#include "chooselock.h"

typedef struct __mutex_t
{
    int flag;
}mutex_t;

void mutex_acquire(mutex_t *lock)
{
    if(xchg(&lock -> flag, 1) == 0)
    {
        return;
    }
    else
    {
        sys_futex(&lock -> flag, FUTEX_WAIT, lock -> flag, 0, 0, 0);
        mutex_acquire(lock);
    }
}

void mutex_release(mutex_t *lock)
{
    xchg(&lock ->flag ,0);
    sys_futex(&lock -> flag, FUTEX_WAKE, 1, 0, 0, 0);
}

void mutex_init(mutex_t *lock)
{
    lock -> flag = 0;
}
