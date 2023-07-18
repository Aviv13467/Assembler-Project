#ifndef HASHTABLE_H
#define HASHTABLE_H
typedef struct item {
    char *key;
    char *value;
    struct item *next;
} item;

typedef struct {
    item **entries;
} hash_table;

item *ht_pair(const char *key, const char *value);
hash_table *ht_create(void);
void ht_set(hash_table *hashtable, const char *key, const char *value);
char *ht_get(hash_table *hashtable, const char *key);
void ht_del(hash_table *hashtable, const char *key);
void ht_free(hash_table *hashtable);

#endif