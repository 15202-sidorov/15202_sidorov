#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cash.h"

static void printf_queue(queue *q)
{
	d_list *current = q->rear;
	while (current != q->front)
	{
		printf("%d -> ",current->digit);
		current = current->right;
	}
	printf("%d\n",current->digit);

	current = q->front;
	while (current != q->rear)
	{
		printf("%d -> ",current->digit);
		current = current->left;
	}
	printf("%d -> ",current->digit);

	return;
}

static void printf_HT(HT *ht)
{
    int i = 0;
    for (i = 0; i < ht->size; i++)
    {
        printf("%d: %d\n",i,(ht->data+i)->digit);
    }

    return;
}



int main(int argc, char **argv)
{
	int digit = 0;
	
	cash *bucket = init_cash(3);
	
	while(1)
	{
		scanf("%d",&digit);
		if (-1 == digit)
		{
			break;
		}
		getchar();
		into_cash(bucket,digit);
		printf_HT(bucket->ht);
		printf_queue(bucket->queue);
	}
	printf("Ready to use the cash: \n");
	while(1)
	{
		scanf("%d",&digit);
		if (-1 == digit)
		{
			break;
		}
		getchar();
		out_of_cash(bucket,digit);
		printf_HT(bucket->ht);
		printf_queue(bucket->queue);

	}

	destroy_cash(bucket);

	return 0;
}