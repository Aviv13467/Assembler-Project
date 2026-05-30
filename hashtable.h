#ifndef HASHTABLE_H
#define HASHTABLE_H

/*** HEADER FILES  ***/
#include <string.h>
#include <stdlib.h>
#include "globals.h"
/*** HEADER FILES  ***/

typedef struct item {
    char *key;
    char *value;
    struct item *next;
} item;

typedef struct {
    item **entries;
} hash_table;

/*
 * hash function is used to deterministically convert a given number to a hash value.
 */
unsigned int hash(char *key);
/*
 * ht_pair function is used to allocate memory and copy strings.
 */
item *ht_pair(char *key, char *value);
/*
 * ht_set is used to assign values to a node which corresponds with the given key.
 */
void ht_set(hash_table *hashtable, char *key, char *value);
/*
 * ht_create function is used to create a hashtable.
 */
hash_table *ht_create(void);
/*
 * ht_get function is used to get the value field of a given entry that matches with the corresponding key.
 */
char *ht_get(hash_table *hashtable, char *key);
/*
 * ht_del function is used to delete an entry from the hashtable.
 */
void ht_del(hash_table *hashtable, char *key);
/*
 * ht_free function is used to delete all entries from the hashtable and free the allocated memory.
 */
void ht_free(hash_table *hashtable);

#endif

