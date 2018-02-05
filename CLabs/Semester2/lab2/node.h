#if !defined(NODE_H)
#define NODE_H



typedef 
	struct NODE // one node of a graph
	{
		int id;
		struct NODE **siblings; // siblings == neighbours
		int *ways; //length to a next sibling  
		int siblings_num; // actual amount of siblings
		int siblings_allowed; // mem allocated
		int visited;
		int dijkstra_value;
	}node;

node *add_sibling(node *old_node,node *addition, int way_to_addition);
node *init_node(int id);
void free_node(node **target_node);


#endif