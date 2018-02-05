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
	void printf_graph_breadth_first_search(node *first_node);
	int dijkstra_search(graph target_graph,int id_1,int id_2);
	void free_graph(graph **target_graph);

#endif