#include "hash_table.h"
#include <stdio.h>

#define STR_MAX_LEN 64

int main(void) {
    htable *ht = htable_new_htable();

    if (!ht)
        exit(1);

    char opt;

    do {
        printf("\nSelect the operation to be made (1: insert an item; 2: delete an item; 3: show the current htable; 4: terminate the program): ");
        scanf("%c", &opt);
        getchar();

        if (opt == '1') {
            char *key = (char *)malloc(STR_MAX_LEN * sizeof(char));

            if (!key) {
                fprintf(stderr, "[-] main(): bad malloc() on 'key'\n");
                htable_delete_htable(ht);
                exit(1);
            }

            char *value = (char *)malloc(STR_MAX_LEN * sizeof(char));

            if (!value) {
                fprintf(stderr, "[-] main(): bad malloc() on 'value'\n");
                htable_delete_htable(ht);
                free(key);
                exit(1);
            }

            scanf("%s", key);
            getchar();
            scanf("%s", value);
            getchar();
            htable_insert(ht, key, value);
            free(key);
            free(value);
        } else if (opt == '2') {
            char *key = (char *)malloc(STR_MAX_LEN * sizeof(char));

            if (!key) {
                fprintf(stderr, "[-] main(): bad malloc() on 'key'\n");
                htable_delete_htable(ht);
                exit(1);
            }

            scanf("%s", key);
            getchar();
            htable_delete(ht, key);
            free(key);
        } else if (opt == '3') {
            htable_show(ht);
        }
    } while (opt != '4');

    htable_delete_htable(ht);

    return 0;
}