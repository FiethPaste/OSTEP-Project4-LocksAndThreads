#include "chooselock.h"

/*typedef struct __mutex_t
{
    unsigned int flag;
}mutex_t;


int bit_test_set(mutex_t *mutex, int bit)
{
    unsigned int set = 0x00000001;
    unsigned int old = mutex -> flag;
    unsigned int newflag = mutex -> flag | (set << bit);
    return ((int)(xchg(&mutex -> flag, newflag)) >= 0) ? 0 : 1;
}

void increment(mutex_t *mutex)
{
    mutex -> flag ++;
}

void decrement(mutex_t *mutex)
{
    mutex -> flag --;
}

int add_zero(mutex_t *mutex, unsigned int add)
{
    mutex -> flag += add;
    return (mutex -> flag == 0) ? 1 : 0;
}*/

/*void futex_wait (mutex_t *mutex, int v)
{
    futex(&mutex -> flag, FUTEX_WAIT, v)
}*/

typedef struct __mutex_t
{
    int flag;
}mutex_t;

int bit_test_set(mutex_t *mutex, int bit)
{
    int old;
    int newflag;
    while(1)
    {
        //int set = 0x00000001;
        //int newflag = mutex -> flag | (set << bit)；
        newflag = mutex -> flag | (1 << bit);
        old = mutex -> flag;
        if(old == mutex -> flag)
        {
            return ((int)(xchg(&mutex -> flag, newflag)) >= 0) ? 0 : 1;
        }
    }
    //return 1;
}

int add_zero(mutex_t *mutex, int add)
{
    int old;
    int newflag;
    while(1)
    {
        newflag = mutex -> flag + add;
        old = mutex -> flag;
        if(mutex -> flag == old)
        {
            return ((int)(xchg(&mutex -> flag, newflag)) == 0x80000000) ? 1 : 0;
        }
    }
}

void mutex_init(mutex_t *mutex)
{
    mutex -> flag = 0;
}

void increment(mutex_t *mutex)
{
    mutex -> flag ++;
}

void decrement(mutex_t *mutex)
{
    mutex -> flag --;
}

void mutex_acquire(mutex_t *mutex)
{
    int v;
    if(bit_test_set(mutex, 31) == 0)
    {
        return;
    }
    increment(mutex);
    while(1)
    {
        if(bit_test_set(mutex, 31) == 0)
        {
            decrement(mutex);
            return;
        }
        v = mutex -> flag;// & 0x7fffffff;
        if(v == 0) continue;
        sys_futex (&mutex -> flag , FUTEX_WAIT, v, NULL, NULL, NULL);
    }
}

void mutex_release(mutex_t *mutex)
{
    if(add_zero(mutex, 0x80000000))
    {
        return;
    }
    //int t = mutex -> flag & 0x7fffffff;
    //xchg(&mutex -> flag, t);
    sys_futex(&mutex -> flag, FUTEX_WAKE, 1, NULL, NULL, NULL);
}
