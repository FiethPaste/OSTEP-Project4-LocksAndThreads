#include "hash.h"

void hash_init(hash_t *hash, int size)
{
    hash -> list = (list_t*)malloc(sizeof(list_t)*size);
    int i;
    for(i = 0; i < size; i++)
    {
        list_init(&hash -> list[i]);
    }
    hash -> buckets = size;
}

void hash_insert(hash_t *hash, unsigned int key)
{
    int bucket = key % (hash -> buckets);
    list_insert(&hash -> list[bucket], key);
}

void hash_delete(hash_t *hash, unsigned int key)
{
    int bucket = key % (hash -> buckets);
    list_delete(&hash -> list[bucket], key);
}

void *hash_lookup(hash_t *hash, unsigned int key)
{
    int bucket = key % (hash -> buckets);
    return list_lookup(&hash -> list[bucket], key);
}

void hash_desdroy(hash_t *hash)
{
    free(hash -> list);
}

int *hashdisplay(hash_t *hash)
{
    int i,j = hash -> buckets;
    int *t = (int*)malloc(sizeof(int) * j);
    for(i = 0;i < 10;i++)
        t[i] = displaynumber(&hash -> list[i]);
    return t;
}
