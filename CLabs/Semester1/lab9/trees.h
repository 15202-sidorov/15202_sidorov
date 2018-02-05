#if !defined(TREES)

#include "inf_s.h"
#define TREES

typedef struct ENTRY
	{
		inf_s name;
		int *arr;
	} entry;

typedef	
	struct BIN_NODE
	{
		entry data;
		struct BIN_NODE *right;
		struct BIN_NODE *left;
		int height;
		int balance;
	} tree;


tree *init_tree(tree *root);
tree *insert_in_tree(tree *root,inf_s name, int d1, int d2);
int *find_in_tree(const tree *root,inf_s name);
tree *destroy_tree(tree *root);
int count_balance(const tree *root);
int height(const tree *root);



#endif