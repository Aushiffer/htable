#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#define HTABLE_INITIAL_SIZE 8
#define HTABLE_PRIME_A 11
#define HTABLE_PRIME_B 17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "prime.h"

// Hash table item structure
typedef struct {
    char *key;
    char *value;
} htable_item;

// Hash table structure
typedef struct {
    size_t size;
    size_t base_size;
    size_t count;
    htable_item **items;
} htable;

// Creates a new hash table
htable *htable_new_htable();

// Deletes a hash table
void htable_delete_htable(htable *htable);

// Inserts a new element on a hash table
void htable_insert(htable *htable, const char *key, const char *value);

// Searches an element on a hash table with the specified key
char *htable_search(htable *htable, const char *key);

// Deletes the element with the specified key from a hash table (ignores the deleted item later on)
void htable_delete(htable *htable, const char *key);

// Prints the non-null or deleted elements of a hash table
void htable_show(htable *htable);

#endif // __HASH_TABLE__