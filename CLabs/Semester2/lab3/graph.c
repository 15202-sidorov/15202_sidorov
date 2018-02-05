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

//checking whether given ids are existing in target_graph
static int are_in_graph(const graph *target_graph,int first_node_id, int second_node_id)
{
	int j = 0;
	int rc = -1;
	for (j = 0; j < target_graph->all_nodes->size; j++)
	{
		if (target_graph->all_nodes->data[j].state != FULL)
		{
			continue;
		}
		if (target_graph->all_nodes->data[j].node_in_graph->id == first_node_id)
		{
			rc++;
		}
		if (target_graph->all_nodes->data[j].node_in_graph->id == second_node_id)
		{
			rc++;
		}
	}
	return rc;
}

/*
	make level graph out of main one 
	refresh distance values
	bfs is used
*/

static int make_level_graph(graph *main_graph,node *first_node, node *second_node)
{
	int i = 0;
	int j = 0;
	//zero distant values in all nodes
	
	for (i = 0; i < main_graph->all_nodes->size; i++)
	{
		if (main_graph->all_nodes->data[i].state == FULL)
		{
			main_graph->all_nodes->data[i].node_in_graph->distance = -1;
			main_graph->all_nodes->data[i].node_in_graph->bfs_visited = 0;
		}

	}
	
	//making another level graph
	//actual bfs
	queue *nodes_queue = init_queue();
	into_queue(nodes_queue,first_node);
	first_node->bfs_visited = 1;
	first_node->distance = 0;
	int current_distance = 0;
	_Bool is_second_node_in_graph = 0;
	while(nodes_queue->number_of_elements != 0)
	{
		_Bool flag = 1;
		node *tmp = out_of_queue(nodes_queue);
		printf("the element drawn %d\n",tmp->id);
		for (j = 0; j < tmp->siblings_num; j++)
		{
			//printf("checking %d\n",tmp->siblings[j]->id);
			if ((!tmp->siblings[j]->bfs_visited) && (tmp->ways[j] > 0))
			{
				//printf("inserting sibilng with id %d in level graph\n",tmp->siblings[j]->id);
				//printf("the way to it is : %d\n",tmp->ways[j]);
				into_queue(nodes_queue, tmp->siblings[j]);
				if (tmp->siblings[j] == second_node)
				{
					is_second_node_in_graph = 1;
				}
				tmp->siblings[j]->bfs_visited = 1;
				tmp->siblings[j]->distance = tmp->distance + 1;
			}
		}
	}
	nodes_queue = free_queue(nodes_queue);
	if (is_second_node_in_graph)
	{
		return 1;
	}
	return 0;
}

void printf_distances(graph *main_graph)
{
	printf("printing the distances of the graph: \n");
	int i = 0;
	for (i = 0; i < main_graph->all_nodes->size; i++)
	{
		if (main_graph->all_nodes->data[i].state == FULL)
		{
			printf("id : %d, distance : %d\n",main_graph->all_nodes->data[i].node_in_graph->id,
					main_graph->all_nodes->data[i].node_in_graph->distance);
		}

	}
	return ;
}

/*
	finding a blocking flow out of level graph 
	memorising the results
	level graph is located in memory as if it is main graph
	dfs is used
*/

static void add_or_increace_back_sibling(node *current_node, node *came_from, int current_flow)
{
	int i = 0;
	for (i = 0; i < current_node->siblings_num; i++)
	{
		if (came_from == current_node->siblings[i])
		{
			current_node->ways[i] += current_flow;
			return;
		}
	}
	current_node = add_sibling(current_node,came_from,current_flow);
	return ;
}

static int find_blocking_flow(	node *current_node,
								node *target_node,
								int coming_in_flow, 
								node *came_from)
{
	if (current_node == target_node)
	{
		if (coming_in_flow <= 0)
		{
			return coming_in_flow;
		}
		printf("one way is found, the flow is %d\n",coming_in_flow);
		int i = 0;
		add_or_increace_back_sibling(current_node,came_from,coming_in_flow);
		return coming_in_flow;
	}
	else
	{
		int i = 0;
		int result = 0;
		_Bool flag = 0; // checking whether there are any possibilities
		int found_flow = 0;
		printf("Current position :\n");
		printf("	current id : %d\n",current_node->id);
		printf("	distnace : %d\n",current_node->distance);
		int siblings_amount = current_node->siblings_num;
		for (i = 0; i < siblings_amount; i++)
		{

			//checking whether it is on the next level of a level graph
			if ((current_node->siblings[i]->distance == current_node->distance + 1)
					&& (current_node->siblings[i]->distance <= target_node->distance)
					&& (current_node->siblings[i]->distance != -1) 
					&& (current_node->ways[i] != 0))
			{
				//at first giving the maximum flow
				printf("current_flow is %d\n",coming_in_flow);
				printf("The node with id %d fits\n",current_node->siblings[i]->id);

				if (current_node->distance == 0)
				{
					found_flow = find_blocking_flow(current_node->siblings[i],
												target_node,
												current_node->ways[i],
												current_node);
					result += found_flow;
					current_node->ways[i] -= found_flow;
					continue;
				}
				if (current_node->ways[i] <= coming_in_flow)
				{

					//giving maximum flow and see what happen
					found_flow = find_blocking_flow(current_node->siblings[i],
													target_node,
													current_node->ways[i],
													current_node);
				}
				else
				{
					found_flow = find_blocking_flow(current_node->siblings[i],
													target_node,
													coming_in_flow,
													current_node);
				}
				current_node->ways[i] -= found_flow;
				coming_in_flow -= found_flow;
				result += found_flow;
				if (coming_in_flow <= 0)
				{
					printf("coming back from id %d\n",current_node->id);
					if (result != 0) 
					{
						add_or_increace_back_sibling(current_node,came_from,result);
					}
					return result;
				}
				
			}
		}
		printf("coming back from id %d\n",current_node->id);
		if ((result != 0) && (current_node->distance != 0))
		{
			add_or_increace_back_sibling(current_node,came_from,result);
		}
		return result;
	}

}

//already got the max flow in graph
//returns the value of the max flow
int max_flow(graph *main_graph,int node_id_1, int node_id_2)
{
	FILE *output_file = fopen("output.txt","w");
	if (are_in_graph(main_graph,node_id_1,node_id_2) != 1)
	{
		return -1;
	}
	node *first_node = find(main_graph->all_nodes,node_id_1);
	node *second_node = find(main_graph->all_nodes,node_id_2);
	//make residual graph
	int result = 0;
	
	while(make_level_graph(main_graph,first_node,second_node))
	{
		printf("level graph is made\n");
		printf_distances(main_graph);
		result += find_blocking_flow(first_node,second_node,0,NULL);
		fprintf(output_file,"current result : %d\n",result);
	}
	
		
	
	printf("final result : %d\n",result);
	fclose(output_file);
	return result;
}