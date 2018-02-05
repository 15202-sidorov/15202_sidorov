#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashtable.h"

#define LOAD_FACTOR (2.0/3)
#define PROBE 1
#define RESIZE_HT 2
#define COUNT_HASH(x,size) ((x) % (size))


static int hash(int id, int size)
{
	return COUNT_HASH(id,size);
}

static void rehash(const HT *old, HT *new)
{
	assert(old);
	int i;
	for (i = 0; i < old->size; i++)
	{
		if (FREE != (old->data+i)->state)
		{
			int index = hash((old->data+i)->node_in_graph->id,new->size); 
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
		(ht->data+i)->node_in_graph = NULL;
		(ht->data+i)->state = FREE; //points that nothing's in here
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

void insert(HT *ht,node *target_node) //liniar probes method
{
	assert(ht);
	//checking the load factor and making rehashing if it's big enough
	
	if(ht->load_fact > LOAD_FACTOR)
	{
		HT *ht_new = create_HT(ht->size*RESIZE_HT);	// creating a new table of a size twice bigger
		rehash(ht,ht_new);
		free(ht->data);
		*ht = *ht_new;
		free(ht_new);
	}
	
	ht->load_fact += 1.0/ht->size;
	//if not, doing the insertion with the liniar probes method 
	int index = hash(target_node->id,ht->size);
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
	(ht->data+index)->node_in_graph = target_node;
	(ht->data+index)->state = FULL;
	
	return;
}

node *find(const HT *ht,int id)
{
	assert(ht);
	int index = hash(id,ht->size);
	while (1)
	{
		
		if (NULL == (ht->data+index)->node_in_graph)
		{
			return NULL;
		}
		if ((ht->data+index)->node_in_graph->id == id)
		{
			return (ht->data+index)->node_in_graph;
		}
		index++;
		if (index >= ht->size)
		{
			index = 0;
		}
	}
}




