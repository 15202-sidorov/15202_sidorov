#if !defined(CASH_GUARD)
#define CASH_GUARD

#include "hashtable.h"
#include "list.h"

typedef	struct CASH
	{
		HT *ht;
		queue *queue;
		int size;
	} cash;

cash *init_cash(int size);
void into_cash(cash *bucket, int element);
void out_of_cash(cash *bucket, int digit); 
void destroy_cash(cash *bucket);





#endif