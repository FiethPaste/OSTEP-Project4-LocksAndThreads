#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "../linklist/linklist.c"

typedef struct __hash_t_
{
    list_t *list;
    int buckets;
}hash_t;

void hash_init(hash_t *hash, int size);
void hash_insert(hash_t *hash, unsigned int key);
void hash_delete(hash_t *hash, unsigned int key);
void *hash_lookup(hash_t *hash, unsigned int key);
void hash_desdroy(hash_t *hash);
int *hashdisplay(hash_t *hash);

#endif // HASH_H_INCLUDED
