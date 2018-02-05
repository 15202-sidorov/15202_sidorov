#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
REMARKS
	Get more examples

*/

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
	int way_to_addition = 0;

	graph *result = init_graph();
	printf("graph_inited\n");

	while (1)
	{
		int rc = fscanf(input_file,"%d %d %d\n",&node_id_1,&node_id_2,&way_to_addition);
		if (rc != 3)
		{
			if (fgetc(input_file) == EOF)
			{
				break;
			}
			fprintf(stderr,"Error in the file: %s\n",file_name);
			return NULL;
		}
		printf("read three simbols %d %d %d\n",node_id_1,node_id_2,way_to_addition);
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
			node_1 = add_sibling(node_1,node_2,way_to_addition);
		}
		else
		{
			//if not, init and add node to the graph and add the sibling to the corrsponging node
			printf("adding node to the graph and adding the corrsponding sibling\n");
			insert(result->all_nodes,node_1);
			node_1 = add_sibling(node_1,node_2,way_to_addition);
		}

		if (!is_in_graph_2)
		{
			printf("adding second node in the graph\n");
			insert(result->all_nodes,node_2);
		}
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
		int i = 0;
		for (i = 0; i < tmp->siblings_num; i++)
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

node *find_min_dejkstra_value(graph target_graph) //around all graph
{
	int i = 0;
	int min_i = -1;
	for (i = 0; i < target_graph.all_nodes->size; i++)
	{

		if (target_graph.all_nodes->data[i].state == FULL) 
		{
			if (!target_graph.all_nodes->data[i].node_in_graph->visited)
			{
				if (-1 == min_i)
				{
					min_i = i;
					continue;
				}
				node *current_node = target_graph.all_nodes->data[i].node_in_graph;
				if ((current_node->dijkstra_value < target_graph.all_nodes->data[min_i].node_in_graph->dijkstra_value)
					&& (current_node->dijkstra_value != -1))
				{
					min_i = i;
				}
			}
		}
	}
	return target_graph.all_nodes->data[min_i].node_in_graph;
}

int dijkstra_search(graph target_graph,int first_node_id, int second_node_id)
{
	node *first_node = find(target_graph.all_nodes,first_node_id);
	node *second_node = find(target_graph.all_nodes,second_node_id);
	first_node->dijkstra_value = 0;
	//giving all the siblings values
	// should check every sibling on wheather is is already visited and whether the new value is more then the old one
	//finding min one 
	//going in there and doing the same thing again until we are in the second node 
	//returning the dejkstra value of the second node
	node *current_node = first_node;
	current_node->visited = 1;
	while (current_node != second_node)
	{
		int i = 0;
		for (i = 0; i < current_node->siblings_num; i++)
		{
			int new_value = current_node->ways[i] + current_node->dijkstra_value;
			if (((!current_node->siblings[i]->visited) && 
					(new_value < current_node->siblings[i]->dijkstra_value)) ||
					(current_node->siblings[i]->dijkstra_value == -1))
			{
				current_node->siblings[i]->dijkstra_value = new_value;
			}

		}
		current_node = find_min_dejkstra_value(target_graph);
		current_node->visited = 1;
	}

	return current_node->dijkstra_value;
}