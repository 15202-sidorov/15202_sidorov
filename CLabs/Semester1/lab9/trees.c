#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "trees.h"

int height(const tree *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		int height_l = height(root->left);
		int height_r = height(root->right);
		if (height_l >= height_r)
		{
			return (1 + height_l);
		}
		else
		{
			return (1 + height_r);
		}
	}
}

int count_balance(const tree *root)
{
	return height(root->right) - height(root->left);
}

static tree *fix_height(tree *root) // makes amendements to the balance of root
{
	int height_l = height(root->left);
	int height_r = height(root->right);

	root->height = (height_l > height_r ? height_l : height_r)+1;
	root->balance = count_balance(root);
	return root;
}

static tree *rotate_right(tree *root)
{
	tree *q = root->left;
	root->left = q->right;
	q->right = root;
	fix_height(root);
	fix_height(q);

	return q;
}

static tree *rotate_left(tree *root)
{
	tree *p = root->right;
	root->right = p->left;
	p->left = root;
	fix_height(root);
	fix_height(p);
	
	return p;
}

static tree *balance(tree* root) // balnce the root
{
	//printf("make balance\n");
	fix_height(root);

	if (2 == root->balance) //need to balance right tree
	{
		if (root->right->balance < 0)
		{
			root->right = rotate_right(root->right);
		}
		return rotate_left(root);
	}
	
	if (-2 == root->balance) //need to balance left tree
	{
		if (root->left->balance > 0)
		{
			root->left = rotate_left(root->left);
		}
		return rotate_right(root);
	}
	
	return root; //no need to balance
}

tree *init_tree(tree *root)
{

	root = (tree *)calloc(1,sizeof(tree));
	root->data.arr = (int *)calloc(2,sizeof(int));
	root->right = NULL;
	root->left = NULL;
	root->height = 0;
	return root;
}

tree *insert_in_tree(tree *root, inf_s name, int d1, int d2)
{
	
	if (NULL == root)
	{
		root = init_tree(root);
		root->data.arr[0] = d1;
		root->data.arr[1] = d2;
		root->data.name = name;
		return root; 
	}
	if (strcmp(name.s,root->data.name.s) < 0)
	{
		root->left = insert_in_tree(root->left,name,d1,d2);
	}
	else 
	{
		root->right = insert_in_tree(root->right,name,d1,d2);
	}
	return balance(root);
}

int *find_in_tree(const tree *root, inf_s name)
{
	if (NULL == root)
	{
		return NULL;
	}
	if (0 == strcmp(root->data.name.s,name.s))
	{
		return root->data.arr;
	}
	if (strcmp(name.s,root->data.name.s) < 0)
	{
		return find_in_tree(root->left,name);
	}
	else 
	{
		return find_in_tree(root->right,name);
	}
}

tree *destroy_tree(tree *root)
{	
	if (NULL == root)
	{
		return;
	}
	else
	{
		destroy_tree(root->right);
		destroy_tree(root->right);
		free(root->data.name.s);
		free(root);
		return;
	}
}
