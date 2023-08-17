#include "hashtable.h"

unsigned int hash(char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    value = value % TABLE_SIZE;
    return value;
}

item *ht_pair(char *key, char *value) {
    item *entry = malloc(sizeof(item) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->value, value);

    entry->next = NULL;

    return entry;
}

hash_table *ht_create(void) {
    int i;
    hash_table *hashtable = malloc(sizeof(hash_table) * 1);

    hashtable->entries = malloc(sizeof(item*) * TABLE_SIZE);
    for (i = 0; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(hash_table *hashtable, char *key, char *value) {
    item *prev;
    unsigned int slot = hash(key);

    item *entry = hashtable->entries[slot];

    if (entry == NULL) { /* Slot is available, insert here */
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    while (entry != NULL) { /* existent key found/collision occurred, search for a matching key for update or traverse to the end and add a new entry */
        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        prev = entry;
        entry = prev->next;
    }

    prev->next = ht_pair(key, value);
}

char *ht_get(hash_table *hashtable, char *key) {
    unsigned int slot = hash(key);

    item *entry = hashtable->entries[slot];

    if (entry == NULL) {
        return NULL;
    }

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }

        entry = entry->next;
    }

    return NULL;
}



void ht_del(hash_table *hashtable, char *key) {
    unsigned int bucket = hash(key);
    item *prev, *entry;
    int idx;
    idx = 0;

    entry = hashtable->entries[bucket];

    if (entry == NULL) {
        return;
    }

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_free(hash_table *hashtable) {
    int i;
    for (i = 0; i < TABLE_SIZE; ++i) {
        item *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }
        for(;;) {
            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }
    }
}
