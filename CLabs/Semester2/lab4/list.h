#if !defined(LIST)
#define LIST

typedef
	enum 
	{
		NO_CHANGE,
		GAP
	}move;

typedef 
	struct DOUBLE_LINKED_LIST
	{
		struct DOUBLE_LINKED_LIST *right;
		struct DOUBLE_LINKED_LIST *left;
		move digit;
	}d_list;

typedef 
	struct QUEUE
	{
		d_list *rear;
		d_list *front;
		int number_of_elements;
	}queue;


queue *init_queue();
void into_queue(queue *q, move elem);
move out_of_queue(queue *q);
//void get_to_the_end(queue *q,d_list *element);

#endif