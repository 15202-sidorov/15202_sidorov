#if !defined(GRAPH_H)
#define GRAPH_H

#include "list.h"
#include "hashtable.h"

typedef 
	struct GRAPH 
	{
		HT *all_nodes; //the array of all nodes in da graph
	} graph;

	graph *make_graph_from_file(const char *file_name);
	void printf_graph_breadth_first_search(node *first_node);
	void free_graph(graph **target_graph);

#endif