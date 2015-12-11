#ifndef CHOOSELOCK_H_INCLUDED
#define CHOOSELOCK_H_INCLUDED

#include <pthread.h>
#include "xchg.c"
#include "sys_futex.c"

#define SPIN_LOCK 1
#define MUTEX_LOCK 2
#define PTHREAD_MUTEX_LOCK 3
#define CUR_LOCK 1

#define MUTEX2 4
#define MUTEX3 5
#define MUTEX4 6
#define CUR_MUTEX 5

#endif // CHOOSELOCK_H_INCLUDED
