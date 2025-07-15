#include "hash_table.h"

int main(void) {
    htable *ht = htable_new_htable();

    if (!ht)
        exit(1);

    htable_insert(ht, "aloha", "banana");
    htable_insert(ht, "tutu", "banana");
    htable_insert(ht, "charlie", "banana");
    htable_insert(ht, "stamper", "banana");
    htable_insert(ht, "chud", "banana");
    htable_insert(ht, "tldr", "banana");
    htable_insert(ht, "afaik", "banana");
    htable_insert(ht, "afaik", "banana");
    htable_insert(ht, "af", "banana");
    htable_insert(ht, "abcdef", "banana");
    htable_insert(ht, "ghghgg", "banana");
    htable_insert(ht, "stringer bell", "banana");
    htable_show(ht);
    htable_delete_htable(ht);

    return 0;
}