#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"

int main(int argc, char **argv)
{
	char *file_name = argv[1];
	graph * new_graph = make_graph_from_file(file_name);
	if (new_graph == NULL)
	{
		return -1;
	}
	printf("%d\n",max_flow(new_graph,atoi(argv[2]),atoi(argv[3])));

	free_graph(&new_graph);
}