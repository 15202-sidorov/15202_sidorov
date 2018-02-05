#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "node.h"

#define START_LENGTH_OF_SIBLINGS 10
#define MULT_SIBLINGS 2

node *add_sibling(node *old_node,node *addition, int way_to_addition) // adding sibling to the node 
{
	old_node->siblings_num++;
	if (way_to_addition <= 0)
	{
		return old_node;
	}
	if (old_node->siblings_num >= old_node->siblings_allowed)
	{
		//adding nodes
		old_node->siblings_allowed *= MULT_SIBLINGS;
		node **new_siblings = (node **)calloc(old_node->siblings_allowed,sizeof(node *));
		memcpy(new_siblings,old_node->siblings,old_node->siblings_num*sizeof(node *));
		new_siblings[old_node->siblings_num-1] = addition;
		free(old_node->siblings);
		old_node->siblings = new_siblings;
		
		//adding ways
		int *new_ways = (int *)calloc(old_node->siblings_allowed,sizeof(int));
		memcpy(new_ways,old_node->ways,old_node->siblings_num*sizeof(int));
		new_ways[old_node->siblings_num-1] = way_to_addition;
		free(old_node->ways);
		old_node->ways = new_ways;

	}
	old_node->siblings[old_node->siblings_num-1] = addition;
	old_node->ways[old_node->siblings_num-1] = way_to_addition;

	return old_node;
}

node *init_node(int id)
{
	node *new_node = (node *)calloc(1,sizeof(node));
	new_node->id = id;
	new_node->siblings_num = 0;
	new_node->siblings_allowed = START_LENGTH_OF_SIBLINGS;
	new_node->siblings = (node **)calloc(START_LENGTH_OF_SIBLINGS,sizeof(node *));
	new_node->ways = (int *)calloc(START_LENGTH_OF_SIBLINGS,sizeof(int));
	new_node->distance = -1;

	return new_node;
}

void free_node(node **target_node)
{
	free((*target_node)->siblings);
	free(*target_node);
	free((*target_node)->ways);

	return;
}

