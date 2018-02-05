#if !defined(HASHTABLE_H)
#define HASHTABLE_H

#include "list.h"


enum entry_state
    {
        FREE,
        DELETED,
        FULL
    };

typedef 
    struct ENTRY
    {
        enum entry_state state;
        d_list *pointer;
        int digit;
    } entry;

typedef 
    struct HashTable
    {
        int size;
        double load_fact;
        entry *data;
    } HT;



HT *create_HT(int size);
void insert(HT *ht, int digit, d_list *pointer);
d_list *find(const HT *ht, int digit);
void destroy_HT(HT *ht);
void delete_from_HT(HT *ht, int digit);

#endif
