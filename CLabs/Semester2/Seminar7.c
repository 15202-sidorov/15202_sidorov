#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

//Huffman's code
typedef
	struct ENTRY
	{
		int freq;
		char simb;
	}Entry;

typedef
	struct NODE
	{
		struct NODE *right;
		struct NODE *left;
		Entry data;
		int is_data;
		int value;
		enum
		{
			NOT_INSERTED,
			INSERTED
		}state;
		
	}Node;


Node *init_node(const Entry *data, Node *right_t, Node *left_t, int value)
{
	Node *new_tree = (Node *)calloc(1,sizeof(Node));
	new_tree->right = right_t;
	new_tree->left = left_t;
	if (data != NULL)
	{
		new_tree->data.freq = data->freq;
		new_tree->data.simb = data->simb;
		new_tree->is_data = 1;
	}
	new_tree->state = NOT_INSERTED;
	if ((right_t != NULL) || (left_t != NULL))
	{
		new_tree->value = value;
	}
	else
	{
		new_tree->value = data->freq;
	}
	
	return new_tree;
}

// should call with the core of the tree
void destroy_tree(Node *current)
{
	if (current == NULL)
	{
		return;
	}
	destroy_tree(current->right);
	destroy_tree(current->left);
	free(current);
	return;
}

//returns the index of node with min value from already built tree
int find_min_from_values(Node **node_arr, int defined_nodes_num)
{
	int min = 0;
	int i = 0;
	while (INSERTED == node_arr[min]->state)
	{
		min++;
	}
	for (i = min+1; i < defined_nodes_num; i++)
	{
		if ((node_arr[i]->value < node_arr[min]->value) && (NOT_INSERTED == node_arr[i]->state))
		{
			min = i;
		}
	}
	return min;
}

//takes an array of entries and makes the haffman's tree out of it
Node *make_huffman_tree_from_entries(const Entry *entry_arr, int char_num)
{
	int number_of_nodes = 2 * char_num - 1;
	Node **whole_tree = (Node **)calloc(number_of_nodes,sizeof(Node *));
	

	//inserting all the values from entries into min_values array
	//inserting all the lists of the tree 
	int i = 0;
	for (i = 0; i < char_num; i++)
	{
		printf("inserting %d..%c\n",entry_arr[i].freq,entry_arr[i].simb);
		whole_tree[i] = init_node(entry_arr+i,NULL,NULL,-1);
	}
	printf("all the charachters are put in the tree\n");
	int defined_nodes_num = char_num;

	for (i = char_num; i < number_of_nodes; i++)
	{
		int min_1 = find_min_from_values(whole_tree,defined_nodes_num);
		whole_tree[min_1]->state = INSERTED;
		int min_2 = find_min_from_values(whole_tree,defined_nodes_num++);
		whole_tree[min_2]->state = INSERTED;
		printf("%d %d are found\n",whole_tree[min_1]->value,whole_tree[min_2]->value);
		whole_tree[i] = init_node(NULL,whole_tree[min_1],whole_tree[min_2],whole_tree[min_1]->value + whole_tree[min_2]->value);
	}

	Node *result = whole_tree[number_of_nodes - 1];
	printf("the core value : %d\n",result->value);
	free(whole_tree);
	return result;
}

//returns the core of the graph
Node *make_tree_from_file(const char *file_name)
{
	FILE *input_file = fopen(file_name,"r");
	if (NULL == input_file)
	{
		fprintf(stderr,"Can't find the file\n");
		return NULL;
	}
	//the values of all kind of frequences in one byte
	int frequences[255] = {0};
	
	//getting all the frequenses
	int char_sum = 0;
	while (1)
	{
		char c = fgetc(input_file);
		if ((c == EOF) || (c == '\n'))
		{
			break;
		}
		if (0 == frequences[c])
		{
			char_sum++;
		}
		frequences[c]++;
	}
	//defining the array of all used charachters we've read from file
	Entry *entry_arr = (Entry *)calloc(char_sum,sizeof(Entry));
	int index = 0;
	for (int i = 0; i < 255; i++)
	{
		if (0 != frequences[i])
		{
			entry_arr[index].freq = frequences[i]; 
			entry_arr[index].simb = (char)i; 
			index++;
		}
	}
	printf("making haffman's tree..\n");
	Node *new_tree = make_huffman_tree_from_entries(entry_arr,char_sum);
	fclose(input_file);
	return new_tree;
}

void printf_tree(Node *current)
{
	if (NULL == current)
	{
		printf("NULL is found\n");
		return;
	}
	printf("%d\n",current->value);
	printf("going right\n");
	printf_tree(current->right);
	printf("coming back\n");
	printf("going left\n");
	printf_tree(current->left);
	printf("coming back\n");
	return;
}

void make_table_out_of_tree(Node *current_node, int *code_table, int code, int counter)
{
	if ((current_node->right == NULL) && (current_node->left == NULL))
	{
		printf("The code of %c is : \n",current_node->data.simb);
		for (int i = 0; i < counter; i++)
		{
			printf("0");
		}
		printf("%d\n",code);
		code_table[current_node->data.simb] = code;
	}
	else 
	{
		counter++;
		code <<=  1;
		code++;
		printf("currnet code : %d\n",code);
		make_table_out_of_tree(current_node->right,code_table,code,counter);
		code--;
		printf("currnet code : %d\n",code);
		make_table_out_of_tree(current_node->left,code_table,code,counter);
		return;
	}
	return;
}

int main()
{
	Node *huffman_tree = make_tree_from_file("target");
	if (NULL == huffman_tree)
	{
		return -1;
	}
	printf("the tree is made...\n");
	printf_tree(huffman_tree);
	
	// the table of all codes in the file
	int code_table[255] = {0};
	make_table_out_of_tree(huffman_tree,code_table,0,0);
	//printf_file_in_huffman_code(code_table);
	
	destroy_tree(huffman_tree);

	return 0;
}