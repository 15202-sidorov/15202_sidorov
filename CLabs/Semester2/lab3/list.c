#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"


static d_list *init_list()
{
	d_list *list = (d_list *)calloc(1,sizeof(d_list));
	list->right = NULL;
	list->left = NULL;

	return list;
}

queue *init_queue()
{
	queue *q = (queue *)calloc(1,sizeof(queue));
	q->number_of_elements = 0;
	q->rear = init_list(q->rear);
	q->front = q->rear;
	
	return q;
}

void into_queue(queue *q, node *elem)
{
	assert(q);
	if (0 == q->number_of_elements)
	{
		q->rear->data = elem;
		q->number_of_elements++;
		return;
	}
	d_list *next_elem = q->rear;
	
	q->rear->left = init_list();
	q->rear = q->rear->left;
	q->rear->data = elem;
	q->rear->right = next_elem;
	q->rear->left = NULL;
	
	next_elem->left = q->rear;

	if (1 == q->number_of_elements)
	{
		q->front = next_elem;
	}

	q->number_of_elements++;
	
	return;
}

node *out_of_queue(queue *q) //draws out the last element out of queue
{
	assert(q);
	if (0 == q->number_of_elements)
	{
		printf("nothing is queue\n");
		return NULL;
	}
	if (1 == q->number_of_elements)
	{
		node *result = q->front->data;
		free(q->front);
		q->front = init_list(q->front);
		q->rear = q->front;
		q->number_of_elements--;
		return result;
	}
	node *result = q->front->data;
	d_list *new_front = q->front->left;
	free(q->front);
	new_front->right = NULL;
	q->front = new_front;
	q->number_of_elements--;
	return result;
}


void printf_queue(queue *q)
{
	assert(q);
	d_list *current = q->rear;
	while (current != NULL)
	{
		printf("%d->",current->data->id);
		current = current->right;
	}
	printf("\n");
	return;
}

queue *free_queue(queue *q)
{
	d_list *current = q->rear;
	while (current->right != NULL)
	{
		current = current->right;
		free(current->left);
	}
	free(q);
	return q;
}

