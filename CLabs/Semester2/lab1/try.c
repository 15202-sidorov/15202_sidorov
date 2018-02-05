#include <stdio.h>

#include "graph.h"

int main()
{
	const char *file_name = "target";
	graph *new_graph = make_graph_from_file(file_name);
	if (new_graph == NULL)
	{
		fprintf(stderr,"Error in da file\n");
		return -1;
	}
	printf("DONE\n");
	printf_graph_breadth_first_search(find(new_graph->all_nodes,0));
	printf("DONE\n");
	free_graph(&new_graph);
	printf("ALL DONE\n");
	return 0;
}