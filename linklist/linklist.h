#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include "../locks/chooselock.h"

#if CUR_MUTEX == MUTEX2
    #include "../locks/mutex2.c"
#elif CUR_MUTEX == MUTEX3
    #include "../locks/mutex3.c"
#else
    #include "../locks/mutex4.c"
#endif

#include "../locks/spinlock.c"

typedef struct __node_t_
{
    int key;
    struct __node_t_ *next;
}node_t;

typedef struct __list_t_
{
    node_t *head;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_t lock;
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_t lock;
    #else
        pthread_mutex_t lock;
    #endif
}list_t;

void list_init(list_t *list);
void list_insert(list_t *list, unsigned int key);
void list_delete(list_t *list, unsigned int key);
void *list_lookup(list_t *list, unsigned int key);
int displaynumber(list_t *list);

#endif // LINKLIST_H_INCLUDED
