#if !defined(GRAPH_H)
#define GRAPH_H

#include "list.h"
#include "hashtable.h"

typedef 
	struct GRAPH 
	{
		HT *all_nodes; //the array of all nodes in da graph
	}graph;

	graph *make_graph_from_file(const char *file_name);
	int max_flow(graph *main_graph, int id_1, int id_2);
	void free_graph(graph **target_graph);

#endif