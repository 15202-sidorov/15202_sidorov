#if !defined(LIST)
#define LIST

#include "node.h"

typedef 
	struct DOUBLE_LINKED_LIST
	{
		struct DOUBLE_LINKED_LIST *right;
		struct DOUBLE_LINKED_LIST *left;
		node *data;
	}d_list;

typedef 
	struct QUEUE
	{
		d_list *rear;
		d_list *front;
		int number_of_elements;
	}queue;


queue *init_queue();
void into_queue(queue *q, node *elem);
node *out_of_queue(queue *q);
void printf_queue(queue *q);
queue *free_queue(queue *q);

#endif