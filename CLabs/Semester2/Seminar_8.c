#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define HEX_FILE_NAME "hex_file"
#define TARGET_FILE_NAME "target"

//decoding file with haffman's tree
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
		int value;
		enum
		{
			NOT_INSERTED,
			INSERTED
		}state;
	}Node;

typedef
	struct BITSTREAM
	{
		FILE *f;
		unsigned char cur_word; //int bits are there
		int cur_bit_id;
	}BitStream;

typedef
	struct TABLE_ELEM
	{
		char simb;
		int sign_bits;
		int bits;
	}Table_elem;


//archiving part
Node *init_node(const Entry *data, Node *right_t, Node *left_t, int value)
{
	Node *new_tree = (Node *)calloc(1,sizeof(Node));
	new_tree->right = right_t;
	new_tree->left = left_t;
	if (data != NULL)
	{
		new_tree->data.freq = data->freq;
		new_tree->data.simb = data->simb;
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
Node *make_tree_from_file(const char *file_name, int *elem_sum)
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
	*elem_sum = char_sum;
	return new_tree;
}

//array Table_elem is already allocated
void make_table(Node *huffman_tree, int current_bits, int *counter, Table_elem **table, int sign_bits_counter)
{
	if  ((huffman_tree->right == NULL) && (huffman_tree->left == NULL))
	{
		printf("inserting in table %c by id %d\n",huffman_tree->data.simb,*counter);
		(*table)[*counter].simb = huffman_tree->data.simb;
		(*table)[*counter].bits = current_bits;
		(*table)[*counter].sign_bits = sign_bits_counter;
		(*counter)++;
		return;
	}
	else
	{
		make_table(huffman_tree->right,current_bits+1,counter,table,sign_bits_counter+1);
		current_bits >>= 1;
		current_bits <<= 1;
		make_table(huffman_tree->left,current_bits,counter,table,sign_bits_counter+1);
		return;
	}
}


//dearchiving part
int next_bit(BitStream *bs) // returns 0 or 1
{
	if (bs->cur_bit_id >= sizeof(char)*8)
	{
		bs->cur_bit_id = 0;
		fread(&(bs->cur_word),sizeof(char),1,bs->f); // reading the next char
	}
	int result = (bs->cur_word >> (sizeof(char)*8 - bs->cur_bit_id - 1)) % 2;
	bs->cur_bit_id++;
	return result;
}

char print_letters(BitStream *bs, Node *Huffman_tree)
{
	while (bs->cur_word != EOF)
	{
		if ((Huffman_tree->right == NULL) && (Huffman_tree->left == NULL))
		{
			printf("%c",Huffman_tree->data.simb);
			return Huffman_tree->data.simb;
		}
		if(next_bit(bs) == 1)
		{
			Huffman_tree = Huffman_tree->right;
		}
		else
		{
			Huffman_tree = Huffman_tree->left;
		}
	}
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

void make_hex(Table_elem *table)
{
	FILE *input_file = fopen(TARGET_FILE_NAME,"r");
	FILE *hex_file = fopen(HEX_FILE_NAME,"w");
	unsigned char c = 0;
	int sign_bits_sum = 0;
	char write_dig = 0;
	int i = 0;
	int addition_bits = 0;
	while (1)
	{
		c = fgetc(input_file);
		if ((EOF == c) || ('\n' == c))
		{
			break;
		}
		i = 0;
		while(c != table[i].simb)
		{
			i++;
		}
		printf("table[i].simb = %c\n",table[i].simb);
		if (sign_bits_sum + table[i].sign_bits > 8)
		{
			addition_bits += 8 - sign_bits_sum;
			write_dig <<= addition_bits;
			write_dig += table[i].bits >> (table[i].sign_bits - addition_bits);
			printf("writing %x\n",write_dig);
			fwrite(&write_dig,1,sizeof(char),hex_file);
			write_dig = 0;
			sign_bits_sum = 0;
		} 
		write_dig <<= table[i].sign_bits;
		write_dig += table[i].bits; 
		sign_bits_sum += table[i].sign_bits;
		printf("write_dig is %d\n",write_dig);
		printf("current bits are %d\n",table[i].bits);
		printf("current sign bits are %d\n",table[i].sign_bits);
		printf("current sum is %d\n",sign_bits_sum);
		
	}
	addition_bits += 8 - sign_bits_sum;
	write_dig <<= addition_bits;
	write_dig += table[i].bits >> (table[i].sign_bits - addition_bits);
	printf("writing %x\n",write_dig);
	fwrite(&write_dig,1,sizeof(char),hex_file);
	fclose(hex_file);
	fclose(input_file);
}

int main()
{
	int number_of_chars = 0;
	Node *huffman_tree = make_tree_from_file(TARGET_FILE_NAME,&number_of_chars); 
	if (NULL == huffman_tree)
	{
		return -1;
	}
	//printf_tree(huffman_tree);
	
	//making table
	Table_elem *table = (Table_elem *)calloc(number_of_chars,sizeof(Table_elem));
	int counter = 0;
	make_table(huffman_tree,0,&counter,&table,0);
	//making hex file
	make_hex(table);
	
	//say, we've put it into the "hex_file"
	FILE *bit_file = fopen(HEX_FILE_NAME,"r");
	BitStream current = {0};
	current.f = bit_file;
	fread(&current.cur_word,sizeof(char),1,bit_file);
	for (int i = 0; i < 18; i++)
	{
		print_letters(&current,huffman_tree);
	}
	printf("\n");
	fclose(bit_file);
	//remove(HEX_FILE_NAME);
	destroy_tree(huffman_tree);
	return 0;
}