#include "hash_table.h"
#include <stddef.h>

// Macro for deletion
static htable_item HTABLE_DELETED_ITEM = {NULL, NULL};

static htable_item *htable_new_htable_item(const char *key, const char *value) {
    htable_item *new_item = (htable_item *)malloc(sizeof(htable_item));

    if (!new_item)
        return NULL;

    new_item->key = strdup(key);
    new_item->value = strdup(value);

    return new_item;
}

static htable *htable_new_htable_of_size(const size_t base_size) {
    htable *new_htable = (htable *)malloc(sizeof(htable));

    if (!new_htable)
        return NULL;

    new_htable->base_size = base_size;
    new_htable->size = next_prime(base_size);
    new_htable->count = 0;
    new_htable->items = (htable_item **)calloc(base_size, sizeof(htable_item *));

    if (!new_htable->items)
        return NULL;

    return new_htable;
}

htable *htable_new_htable() {
    return htable_new_htable_of_size(HTABLE_INITIAL_SIZE);
}

static void htable_resize(htable *htable_rsize, const size_t base_size) {
    if (base_size < HTABLE_INITIAL_SIZE) return;

    htable *new_htable = htable_new_htable_of_size(base_size);

    if (!new_htable)
        exit(1);

    for (size_t i = 0; i < htable_rsize->base_size; i++) {
        htable_item *current = htable_rsize->items[i];

        if (current != NULL && current != &HTABLE_DELETED_ITEM)
            htable_insert(new_htable, current->key, current->value);
    }

    const int tmp_base_size = htable_rsize->base_size;
    htable_rsize->base_size = new_htable->base_size;
    new_htable->base_size = tmp_base_size;

    htable_rsize->count = new_htable->count;

    // Swaps new (resized) with old attributes
    const int tmp_size = htable_rsize->size;
    htable_rsize->size = new_htable->size;
    new_htable->size = tmp_size;

    htable_item **tmp_items = htable_rsize->items;
    htable_rsize->items = new_htable->items;
    new_htable->items = tmp_items;

    htable_delete_htable(new_htable);
}

static void htable_resize_up(htable *htable) {
    const int resize_size = htable->size << 1;
    htable_resize(htable, resize_size);
}

static void htable_resize_down(htable *htable) {
    const int resize_size = htable->size >> 1;
    htable_resize(htable, resize_size);
}

static void htable_delete_htable_item(htable_item *item) {
    free(item->key);
    free(item->value);
    free(item);
}

void htable_delete_htable(htable *htable) {
    for (size_t i = 0; i < htable->base_size; i++) {
        htable_item *current = htable->items[i];

        if (current != NULL && current != &HTABLE_DELETED_ITEM)
            htable_delete_htable_item(current);
    }

    free(htable->items);
    free(htable);
}

static int htable_hash_function(const char *str, const int p, const int n_buckets) {
    long hash_num = 0;
    const size_t str_len = strlen(str);

    for (size_t i = 0; i < str_len; i++) {
        // Converts the string into some large number and fits it into the buckets
        hash_num += ((long)pow(p, str_len - (i + 1)) * str[i]);
        hash_num = hash_num % n_buckets;
    }

    return (int)hash_num;
}

static int htable_get_hash(const char *str, const int n_buckets, const int attempt) {
    int fst_hash = htable_hash_function(str, HTABLE_PRIME_A, n_buckets);
    int snd_hash = htable_hash_function(str, HTABLE_PRIME_B, n_buckets);

    // Double hashing
    return (fst_hash + attempt * (snd_hash + 1)) % n_buckets;
}

void htable_insert(htable *htable, const char *key, const char *value) {
    const int load = htable->count * 100 / htable->base_size;

    if (load > 70)
        htable_resize_up(htable);
    
    htable_item *new_item = htable_new_htable_item(key, value);

    if (!new_item)
        exit(1);

    size_t index = htable_get_hash(key, htable->base_size, 0);
    size_t attempt = 1;
    htable_item *current = htable->items[index];

    while (current != NULL) {
        // Updates item if necessary
        if (current != &HTABLE_DELETED_ITEM && strcmp(key, current->key) == 0) {
            htable_delete_htable_item(current);
            htable->items[index] = new_item;

            return;
        }

        index = htable_get_hash(key, htable->base_size, attempt);
        current = htable->items[index];
        attempt++;
    }

    htable->items[index] = new_item;
    htable->count++;
}

char *htable_search(htable *htable, const char *key) {
    size_t index = htable_get_hash(key, htable->base_size, 0);
    size_t attempt = 1;
    htable_item *current = htable->items[index];

    while (current != NULL) {
        if (current != &HTABLE_DELETED_ITEM && strcmp(key, current->key) == 0)
            return current->value;

        index = htable_get_hash(key, htable->base_size, attempt);
        current = htable->items[index];
        attempt++;
    }

    return NULL;
}

void htable_delete(htable *htable, const char *key) {
    const int load = htable->count * 100 / htable->size;

    if (load < 10)
        htable_resize_down(htable);

    size_t index = htable_get_hash(key, htable->base_size, 0);
    size_t attempt = 1;
    htable_item *current = htable->items[index];

    while (current != NULL) {
        if (current != &HTABLE_DELETED_ITEM && strcmp(key, current->key) == 0) {
            htable_delete_htable_item(current);
            htable->items[index] = &HTABLE_DELETED_ITEM;
        }

        index = htable_get_hash(key, htable->base_size, attempt);
        current = htable->items[index];

        if (current == NULL)
            htable->count--;

        attempt++;
    }
}

void htable_show(htable *htable) {
    printf("%lu items\n", htable->count);

    for (size_t i = 0; i < htable->base_size; i++) {
        if (htable->items[i] != NULL && htable->items[i] != &HTABLE_DELETED_ITEM)
            printf("%s: %s\n", htable->items[i]->key, htable->items[i]->value);
    }
}