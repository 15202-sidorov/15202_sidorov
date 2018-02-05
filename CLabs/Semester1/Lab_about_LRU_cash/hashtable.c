#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

#define LOAD_FACTOR (2.0/3)
#define PROBE 1
#define RESIZE_HT 2
#define COUNT_HASH(x,size) (x % size)

static void rehash(const HT *old, HT *new)
{
    assert(old);
    int i;
    for (i = 0; i < old->size; i++)
    {
        if (FULL == (old->data+i)->state)
        {
            int index = COUNT_HASH((old->data+i)->digit,new->size);
            while ((new->data+index)->state != FREE)
            {
                index++;
                if (index > new->size)
                {
                    index = 0;
                }
            }
            new->data[index] = old->data[i];
            new->load_fact += 1.0/new->size;
        }

    }
    return;
}

HT *create_HT(int size)
{
    HT *ht = (HT *)malloc(sizeof(HT));
    ht->size = size;
    ht->load_fact = 0;
    ht->data = (entry *)calloc(size,sizeof(entry));
    int i = 0;
    for (i = 0; i < size; i++)
    {
        (ht->data+i)->state = FREE; //points that nothing's in here
        ht->data->pointer = NULL;
    }

    return ht;
}

void destroy_HT(HT *ht)
{
    int i = 0;
    int size = ht->size;
    free(ht->data);
    free(ht);
    
    return;
}

void insert(HT *ht, int digit, d_list *pointer) 
{
    assert(ht);
    ht->load_fact += 1.0/ht->size;
    if(ht->load_fact > LOAD_FACTOR)
    {
        HT *ht_new = create_HT(ht->size*RESIZE_HT);    
        rehash(ht,ht_new);
        *ht = *ht_new;
        free(ht_new);
    }
    int index = COUNT_HASH(digit,ht->size);
    int count = 0;
    while (FULL == (ht->data+index)->state)
    {
        index++;
        if (index > ht->size)
        {
            index = 0;
        };
    }
    (ht->data+index)->digit = digit;
    (ht->data+index)->pointer = pointer;
    (ht->data+index)->state = FULL;

    return;
}

d_list *find(const HT *ht, int digit)
{
    assert(ht);
    int index = COUNT_HASH(digit,ht->size);
    
    while (digit != (ht->data+index)->digit)
    {
        if (FREE == (ht->data+index)->state)
        {
            return NULL;
        }
        index++;
        if (index > ht->size)
        {
            index = 0;
        }
        
    }

    if ((digit == 0) && ((ht->data+index)->state != FULL))
    {
        return NULL;
    }
    
    return (ht->data+index)->pointer;
}

void delete_from_HT(HT *ht, int digit)
{
    int index = COUNT_HASH(digit,ht->size);

    while (digit != (ht->data+index)->digit)
    {
        index++;
        if (index > ht->size)
        {
            index = 0;
        }
        if (FREE == ht->data->state)
        {
            return;
        }
    }

    printf("DELETING ELEMENT : %d\n",(ht->data+index)->digit);

    (ht->data+index)->state = DELETED;
    free((ht->data+index)->pointer);
    (ht->data+index)->digit = 0; 
    ht->load_fact -= 1.0/ht->size;

    return;
}





