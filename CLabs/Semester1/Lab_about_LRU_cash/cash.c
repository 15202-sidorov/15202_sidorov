#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cash.h"

cash *init_cash(int size)
{
	cash *bucket = (cash *)calloc(1,sizeof(cash));
	bucket->ht = create_HT(size);
	bucket->size = size;
	bucket->queue = init_queue();

	return bucket;
}

void into_cash(cash *bucket,int element)
{
	if (bucket->queue->number_of_elements == bucket->size)
	{
		 int deleted_el = out_of_queue(bucket->queue);
		 delete_from_HT(bucket->ht,deleted_el);
	}	 
	into_queue(bucket->queue,element);
	insert(bucket->ht,element,bucket->queue->rear);

	return;
}

void out_of_cash(cash *bucket, int digit)
{
	d_list *adress = find(bucket->ht,digit);
	if (NULL == adress)
	{
		return;
	}
	printf("found :%d\n",adress->digit);
	get_to_the_end(bucket->queue,adress); 
	
	return ;
}	

void destroy_cash(cash *bucket)
{
	destroy_HT(bucket->ht);
	return;
}

