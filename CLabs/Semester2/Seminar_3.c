#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

#define START_POINT 0

typedef 
	struct NODE
	{
		int id;
		struct NODE **siblings;
		int siblings_num;
	}node;

typedef 
	struct WAY
	{
		int number_of_ways; // to one direction !!!
		int gone;
	}way;


int fit_or_not(node *graph)
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		if (graph[i].siblings_num % 2 == 1)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	return 1;
}

void make_step(node *graph,way visited[10][10],queue *result)
{
	int i = 0;
	for (i = 0; i < graph->siblings_num; i++)
	{
		if (visited[graph->siblings[i]->id][graph->id].number_of_ways > 0)
		{
			if (visited[graph->siblings[i]->id][graph->id].number_of_ways > (visited[graph->siblings[i]->id][graph->id].gone))
			{
				visited[graph->siblings[i]->id][graph->id].gone++;
				visited[graph->siblings[i]->id][graph->id].gone++;
				printf("%d\n",graph->id);
				make_step(graph->siblings[i],visited,result);
			}
		}
		else if (!visited[graph->siblings[i]->id][graph->id].gone)
		{
			visited[graph->siblings[i]->id][graph->id].gone = 1;
			visited[graph->id][graph->siblings[i]->id].gone = 1;
			printf("%d\n",graph->id);
			make_step(graph->siblings[i],visited,result);
		} 
	}
	printf("%d\n",graph->id);
	into_queue(result,graph->id);
	printf("going back\n");
	return;
}

int main()
{
	node graph[10];
	int i = 0;
	way visited[10][10] = {0};
	queue *result = init_queue();

	
	//defining the graph
	graph[0].id = 0;
	graph[0].siblings_num = 2;
	int siblings_num = graph[0].siblings_num;
	graph[0].siblings = (node **)calloc(2,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[0].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[0].siblings[0] = &graph[1];
	graph[0].siblings[1] = &graph[3];
	

	graph[1].id = 1;
	graph[1].siblings_num = 4;
	siblings_num = graph[1].siblings_num;
	graph[1].siblings = (node **)calloc(4,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[1].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[1].siblings[0] = &graph[9];
	graph[1].siblings[1] = &graph[7];
	graph[1].siblings[2] = &graph[2];
	graph[1].siblings[3] = &graph[0];


	graph[2].id = 2;
	graph[2].siblings_num = 4;
	siblings_num = graph[2].siblings_num;

		graph[2].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[2].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[2].siblings[0] = &graph[1];
	graph[2].siblings[1] = &graph[3];
	graph[2].siblings[2] = &graph[4];
	graph[2].siblings[3] = &graph[6];


	graph[3].id = 3;
	graph[3].siblings_num = 2;
	siblings_num = graph[3].siblings_num;
	graph[3].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[3].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[3].siblings[0] = &graph[0];
	graph[3].siblings[1] = &graph[2];
	
	graph[4].id = 4;
	graph[4].siblings_num = 2;
	siblings_num = graph[4].siblings_num;
	graph[4].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[4].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[4].siblings[0] = &graph[5];
	graph[4].siblings[1] = &graph[2];


	graph[5].id = 5;
	graph[5].siblings_num = 2;
	siblings_num = graph[5].siblings_num;
	graph[5].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[5].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[5].siblings[0] = &graph[4];
	graph[5].siblings[1] = &graph[6];


	graph[6].id = 6;
	graph[6].siblings_num = 4;
	siblings_num = graph[6].siblings_num;
	graph[6].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[6].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[6].siblings[0] = &graph[5];
	graph[6].siblings[1] = &graph[2];
	graph[6].siblings[2] = &graph[7];
	graph[6].siblings[3] = &graph[7];
	visited[6][7].number_of_ways = 2;



	graph[7].id = 7;
	graph[7].siblings_num = 4;
	siblings_num = graph[7].siblings_num;
	graph[7].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[7].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[7].siblings[0] = &graph[1];
	graph[7].siblings[1] = &graph[6];
	graph[7].siblings[2] = &graph[8];
	graph[7].siblings[3] = &graph[6];
	visited[7][6].number_of_ways = 2;


	graph[8].id = 8;
	graph[8].siblings_num = 2;
	siblings_num = graph[8].siblings_num;
	graph[8].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[8].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[8].siblings[0] = &graph[7];
	graph[8].siblings[1] = &graph[9];

	graph[9].id = 9;
	graph[9].siblings_num = 2;
	siblings_num = graph[9].siblings_num;
	graph[9].siblings = (node **)calloc(siblings_num,sizeof(node *));
	for (i = 0; i < siblings_num; i++)
	{
		graph[9].siblings[i] = (node *)calloc(1,sizeof(node));
	}
	graph[9].siblings[0] = &graph[1];
	graph[9].siblings[1] = &graph[8];


	if (fit_or_not(graph))
	{
		printf("FITS\n");
		make_step(graph,visited,result);
	}
	else
	{
		printf("DOESN'T FIT\n");
	}
	printf_queue(result);
	free_queue(result);


	return 0;
}