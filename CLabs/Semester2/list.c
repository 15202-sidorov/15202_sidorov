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

void printf_queue(queue *q)
{
	d_list *current = q->rear;
	while (current != q->front)
	{
		printf("%d -> ",current->digit);
		current = current->right;
	}
	printf("%d\n",current->digit);

	return;
}

queue *init_queue()
{
	queue *q = (queue *)calloc(1,sizeof(queue));
	q->number_of_elements = 0;
	q->rear = init_list(q->rear);
	q->front = q->rear;
	
	return q;
}

void into_queue(queue *q, int elem)
{
	assert(q);
	if (0 == q->number_of_elements)
	{
		q->rear->digit = elem;
		q->number_of_elements++;
		return;
	}
	d_list *next_elem = q->rear;
	
	q->rear->left = init_list();
	q->rear = q->rear->left;
	q->rear->digit = elem;
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

int out_of_queue(queue *q)
{
	assert(q);
	int result = q->front->digit;
	d_list *new_front = q->front->left;
	d_list *old_front = q->front;
	new_front->right = NULL;
	q->front = new_front;
	q->number_of_elements--;
	return result;
}

void get_to_the_end(queue *q, d_list *element) //doesn't work yet
{
	assert(q);
	assert(element);
	if (q->rear == element)
	{
		return;
	}
	if (q->front == element)
	{
		int digit = out_of_queue(q);
		into_queue(q,digit);
		return;
	}
	(element->right)->left = element->left;
	(element->left)->right = element->right;
	element->left = NULL;
	d_list *next_to = q->rear;
	next_to->left = element;
	element->right = next_to;
	q->rear = element;
	
	return;
}

void free_queue(queue *q)
{
	d_list *current = q->front;
	while (current->right != NULL)
	{
		current = current->right;
		free(current->left);

	}
	free(q);

	return;
}