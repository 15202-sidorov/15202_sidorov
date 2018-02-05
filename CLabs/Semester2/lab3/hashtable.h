#if !defined(HASHTABLE_H)
#define HASHTABLE_H

#include "node.h"

#define START_SIZE_HT 10

enum entry_state
{
	FULL,
	FREE,
	DELETED
};

typedef struct ENTRY
	{
		node *node_in_graph;
		enum entry_state state;
	} entry;

typedef struct HashTable
	{
		int size;
		double load_fact;
		entry *data;
	}HT;

HT *create_HT(int size);
void insert(HT *ht,node *target_node);
node *find(const HT *ht,int id); // if NULL - means we didn't find anything
void destroy_HT(HT *ht);

#endif