#if !defined(HASHTABLE_H)
#define HASHTABLE_H

#include "inf_s.h"
#define START_SIZE_HT 10

enum entry_state
{
	FULL,
	FREE,
	DELETED
};

typedef struct ENTRY
	{
		inf_s name;
		int arr[2];
		enum entry_state state;
	} entry;

typedef struct HashTable
	{
		int size;
		double load_fact;
		entry *data;
	} HT;

HT *create_HT(int size);
void insert(HT *ht,inf_s name,int d1, int d2);
int *find(const HT *ht,inf_s name);
void destroy_HT(HT *ht);

#endif