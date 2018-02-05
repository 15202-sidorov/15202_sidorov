#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"

#define START_LENGTH_OF_GRAPH 10
#define MULT_NODES 2

static graph *init_graph()
{
	graph *new_graph = (graph *)calloc(1,sizeof(graph));

	new_graph->all_nodes = create_HT(START_LENGTH_OF_GRAPH);

	return new_graph;
}

void free_graph(graph **target_graph) 
{
	int i = 0; 
	printf("freeing all the nodes\n");
	for (i = 0; i < (*target_graph)->all_nodes->size; i++)
	{
		if ((*target_graph)->all_nodes->data[i].node_in_graph != NULL)
		{
			free_node(&(*target_graph)->all_nodes->data[i].node_in_graph);
		}
		
	}
	printf("all nodes are freed\n");
	destroy_HT((*target_graph)->all_nodes);
	free(*target_graph);
	return;
}

graph *make_graph_from_file(const char *file_name)
{
	FILE *input_file = fopen(file_name,"r");
	if (NULL == input_file)
	{
		fprintf(stderr,"Can't open file %s\n",file_name);
		return NULL;
	}
	
	int node_id_1 = 0;
	int node_id_2 = 0;

	graph *result = init_graph();
	printf("graph_inited\n");

	while (1)
	{
		int rc = fscanf(input_file,"%d %d\n",&node_id_1,&node_id_2);
		if (rc != 2)
		{
			if (fgetc(input_file) == EOF)
			{
				break;
			}
			return NULL;
		}
		printf("read two simbols %d %d\n",node_id_1,node_id_2);
		//for each node !separately!
		//check whether the node is already in graph

		//finding or defining all the two nodes
		node *node_1 = find(result->all_nodes,node_id_1);
		node *node_2 = find(result->all_nodes,node_id_2);
		printf("all nodes found\n");
		int is_in_graph_1 = 1;
		int is_in_graph_2 = 1;
		if (node_1 == NULL)
		{	
			node_1 = init_node(node_id_1);
			printf("new node\n");
			is_in_graph_1 = 0;
		}
		else
		{
			printf("old node found\n");
		}
		if (node_2 == NULL)
		{
			node_2 = init_node(node_id_2);
			printf("new node\n");
			is_in_graph_2 = 0;
		}
		else
		{
			printf("old node found\n");
		}
		
		
		if (is_in_graph_1)
		{
			//if yes, add the sibling to the corresponding node 
			printf("adding the sibling to the existing node\n");
			node_1 = add_sibling(node_1,node_2);
		}
		else
		{
			//if not, init and add node to the graph and add the sibling to the corrsponging node
			printf("adding node to the graph and adding the corrsponding sibling\n");
			insert(result->all_nodes,node_1);
			node_1 = add_sibling(node_1,node_2);
		}

		if (is_in_graph_2)
		{
			printf("adding the sibling to the existing node\n");
			node_2 = add_sibling(node_2,node_1);
		}
		else
		{
			printf("adding node to the graph and adding the corrsponding sibling\n");
			insert(result->all_nodes,node_2);
			node_2 = add_sibling(node_2,node_1);
		}
		printf("printing the HT: \n");
		
	}
	
	close(input_file);
	return result;
}

void printf_graph_breadth_first_search(node *first_node)
{
	
	queue *nodes_queue = init_queue();
	printf("queue is initialised\n");
	into_queue(nodes_queue,first_node);
	first_node->visited = 1;
	
	while(nodes_queue->number_of_elements != 0)
	{
		node *tmp = out_of_queue(nodes_queue);
		printf("%d ",tmp->id);
		for (int i = 0; i < tmp->siblings_num; i++)
		{
			if (!tmp->siblings[i]->visited)
			{
				into_queue(nodes_queue, tmp->siblings[i]);
				tmp->siblings[i]->visited = 1;
			}
		}
	}
	printf("\n");

	nodes_queue = free_queue(nodes_queue);

	return;
}