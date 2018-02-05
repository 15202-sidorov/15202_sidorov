#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

#define LOAD_FACTOR (2.0/3)
#define PROBE 1
#define RESIZE_HT 2
#define COUNT_HASH(x,size) (x % size)

static int cmp_str(inf_s s1, inf_s s2)
{
	int i = 0;
	if (s1.count != s2.count)
	{
		return 0;
	}
	while (s1.s[i] != '\0')
	{
		if (s1.s[i] != s2.s[i])
		{
			return 0;
		}
		i++;
	}
	return 1;
}

static int hash(const char *name,int HT_size) // counting the value of key in table 
{
	assert(name);
	int i = 0;
	int sum = 0;
	while ('\0' != name[i])
	{
		sum += COUNT_HASH(name[i],HT_size);
		i++;
	}
	return COUNT_HASH(sum,HT_size);
}

static void rehash(const HT *old, HT *new)
{
	assert(old);
	int i;
	for (i = 0; i < old->size; i++)
	{
		if (FREE != (old->data+i)->state)
		{
			int index = hash((old->data+i)->name.s,new->size); 
			while (FREE != (new->data+index)->state)
			{
				index++;
				if (index > new->size)
				{
					index = 0;
				}
			}
			new->data[index] = old->data[i];
		}
	}
	new->load_fact = old->load_fact * old->size/new->size;

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
		(ht->data+i)->arr[0] = 0;
		(ht->data+i)->arr[1] = 0;
		(ht->data+i)->state = FREE; //points that nothing's in here
		init_s(&((ht->data+i)->name)); 
	}
	
	return ht;
}

void destroy_HT(HT *ht)
{
	int i = 0;
	int size = 0;
	free(ht->data);
	free(ht);
	return;
}

void insert(HT *ht,inf_s name,int d1,int d2) //liniar probes method
{
	assert(ht);
	//checking the load factor and making rehashing if it's big enough
	
	if(ht->load_fact > LOAD_FACTOR)
	{
		HT *ht_new = create_HT(ht->size*RESIZE_HT);	// creating a new table of a size twice bigger
		rehash(ht,ht_new);
		*ht = *ht_new;
		free(ht_new);
	}
	
	ht->load_fact += 1.0/ht->size;
	//if not, doing the insertion with the liniar probes method 
	int index = hash(name.s,ht->size);
	int count = 0;
	while (FREE != (ht->data+index)->state)
	{
		index++;
		if (index > ht->size)
		{
			index = 0;
		}
		count++;
	}
	(ht->data+index)->name = name;
	(ht->data+index)->arr[0] = d1;
	(ht->data+index)->arr[1] = d2;
	(ht->data+index)->state = FULL;
	
	return;
}

int *find(const HT *ht,inf_s name)
{
	assert(ht);
	int index = hash(name.s,ht->size);
	while (!cmp_str((ht->data+index)->name,name))
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
	return (ht->data+index)->arr;
}




