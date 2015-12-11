#include "chooselock.h"
#define TIME 100

typedef struct __mutex_t
{
    int flag;
}mutex_t;

void mutex_acquire(mutex_t *lock)
{
    int i = 0;
    while((i++) < TIME);
    {
        if(xchg(&lock -> flag, 1) == 0) return;
    }
    while(1)
    {
        if(xchg(&lock -> flag, 1) == 0)
        {
            return;
        }
        sys_futex (&lock -> flag, FUTEX_WAIT, lock -> flag, 0, 0, 0);
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
