#if !defined(NODE_H)
#define NODE_H



typedef 
	struct NODE // one node of a graph
	{
		int id;
		struct NODE **siblings; // siblings == neighbours
		int *ways; //capacity to a next sibling
		int siblings_num; // actual amount of siblings
		int siblings_allowed; // mem allocated
		int bfs_visited;
		int distance; // also indicates that the node is in level graph
	}node;

node *add_sibling(node *old_node,node *addition, int way_to_addition);
node *init_node(int id);
void free_node(node **target_node);


#endif