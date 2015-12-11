#include "linklist.h"

void list_init(list_t *list)
{
    list -> head = NULL;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_init(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_init(&list -> lock);
    #else
        pthread_mutex_init(&list -> lock, NULL);
    #endif
}

void list_insert(list_t *list, unsigned int key)
{

    node_t *new = (node_t*)malloc(sizeof(node_t));
    if(new == NULL)
    {
        perror("malloc");
        return;
    }
    new -> key = key;
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&list -> lock);
        new -> next = list -> head;
        list -> head = new;
        spinlock_release(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&list -> lock);
        new -> next = list -> head;
        list -> head = new;
        mutex_release(&list -> lock);
    #else
        pthread_mutex_lock(&list -> lock);
        new -> next = list -> head;
        list -> head = new;
        pthread_mutex_unlock(&list -> lock);
    #endif
}

void list_delete(list_t *list, unsigned int key)
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&list -> lock);
    #else
        pthread_mutex_lock(&list -> lock);
    #endif
    node_t *t = list -> head;
    if(t != NULL)
    {
        if(t -> key == key)
        {
            list -> head = list -> head -> next;
            free(t);
            #if CUR_LOCK == SPIN_LOCK
                spinlock_release(&list -> lock);
            #elif CUR_LOCK == MUTEX_LOCK
                mutex_release(&list -> lock);
            #else
                pthread_mutex_unlock(&list -> lock);
            #endif
            return;
        }
    }
    while(t -> next != NULL)
    {
        if(t -> next -> key == key)
        {
            node_t *d = t -> next;
            t -> next = t -> next -> next;
            free(d);
            #if CUR_LOCK == SPIN_LOCK
                spinlock_release(&list -> lock);
            #elif CUR_LOCK == MUTEX_LOCK
                mutex_release(&list -> lock);
            #else
                pthread_mutex_unlock(&list -> lock);
            #endif
            return;
        }
        else t = t -> next;
    }
    #if CUR_LOCK == SPIN_LOCK
        spinlock_release(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_release(&list -> lock);
    #else
        pthread_mutex_unlock(&list -> lock);
    #endif
}

void *list_lookup(list_t *list, unsigned int key)
{
    #if CUR_LOCK == SPIN_LOCK
        spinlock_acquire(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_acquire(&list -> lock);
    #else
        pthread_mutex_lock(&list -> lock);
    #endif
    node_t *curr = list -> head;
    while(curr != NULL)
    {
        if(curr -> key == key)
        {
            break;
        }
        curr = curr -> next;
    }
    #if CUR_LOCK == SPIN_LOCK
        spinlock_release(&list -> lock);
    #elif CUR_LOCK == MUTEX_LOCK
        mutex_release(&list -> lock);
    #else
        pthread_mutex_unlock(&list -> lock);
    #endif
    return (void*)curr;
}

int displaynumber(list_t *list)
{
    int i = 0;
    node_t *t = list -> head;
    while(t != NULL)
    {
        i++;
        t = t -> next;
    }
    return i;
}



