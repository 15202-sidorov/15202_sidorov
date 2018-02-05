#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>

#define HEX_FILE_NAME "hex_file"
#define INPUT_FILE_NAME "test_fibonachi.txt"


//Compressing file with huffmans tree
/*	REMARKS
	table is incorrect the code may be more then 32 bits so we should make an array
	frequency may be more then int change to int64
*/
typedef
	struct ENTRY
	{
		int64_t freq;
		unsigned char simb;
	}Entry;

typedef
	struct NODE
	{
		struct NODE *right;
		struct NODE *left;
		Entry data;
		
		// the sum frequences or the frequency itself
		int64_t value;
		
		// shows whether the node is already inserted in the final tree or just initialized
		enum 
		{
			NOT_INSERTED,
			INSERTED
		}state; 
	}Node;

//the type for final table of all bytes which are in file
typedef
	struct TABLE_ELEM
	{
		unsigned char simb;
		unsigned int bits[16];
		unsigned int sign_bits;
	}Table_elem; 

//bits flow which will be written in commpressed file
typedef
	struct BITS_FLOW
	{
		unsigned int buffer_int;
		unsigned int sign_bits; // in buffer
		FILE *file;
	}bits_flow;

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

//returns the index of node with min value from yet not inserted nodes
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
		whole_tree[i] = init_node(entry_arr+i,NULL,NULL,-1);
	}
	int defined_nodes_num = char_num;

	for (i = char_num; i < number_of_nodes; i++)
	{
		int min_1 = find_min_from_values(whole_tree,defined_nodes_num);
		whole_tree[min_1]->state = INSERTED;
		int min_2 = find_min_from_values(whole_tree,defined_nodes_num++);
		whole_tree[min_2]->state = INSERTED;
		whole_tree[i] = init_node(NULL,whole_tree[min_1],whole_tree[min_2],whole_tree[min_1]->value + whole_tree[min_2]->value);
	}

	Node *result = whole_tree[number_of_nodes - 1];
	printf("the final sum is : %d\n",result->value);
	free(whole_tree);
	return result;
}

//returns the core of the graph
Node *make_tree_from_file(const char *file_name, unsigned int *elem_sum, int64_t *amount_of_symbols)
{
	FILE *input_file = fopen(file_name,"r");
	if (NULL == input_file)
	{
		fprintf(stderr,"Can't find the file\n");
		return NULL;
	}
	//the values of all kind of frequences in one byte
	int64_t frequences[256] = {0};
	
	//getting all the frequenses
	unsigned int char_sum = 0;
	while (1)
	{
		unsigned char c;
		int rc = fread(&c,1,sizeof(char),input_file);
		(*amount_of_symbols)++;
		if (rc != 1)
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
	for (int i = 0; i < 256; i++)
	{
		if (0 != frequences[i])
		{
			entry_arr[index].freq = frequences[i]; 
			entry_arr[index].simb = (char)i; 
			index++;
		}
	}
	Node *new_tree = make_huffman_tree_from_entries(entry_arr,char_sum);
	fclose(input_file);
	free(entry_arr);
	*elem_sum = char_sum;
	return new_tree;
}

//array Table_elem is already allocated

//moves left all the bits in the array 
void move_left(unsigned int bits[16])
{
	int i = 0;
	unsigned int addition = (bits[0] >> 31);
	unsigned int new_addition = 0;
	bits[0] <<= 1;
	for (i = 0; i < 15; i++)
	{
		new_addition = (bits[i+1] >> 31);
		bits[i+1] <<= 1;
		bits[i+1] += addition;
		addition = new_addition;
	}
	return;
}

void make_table(Node *huffman_tree, unsigned int current_bits[16], unsigned int *counter, Table_elem **table, int sign_bits_counter)
{
	if  ((huffman_tree->right == NULL) && (huffman_tree->left == NULL))
	{

		(*table)[*counter].simb = huffman_tree->data.simb;
		memcpy((*table)[*counter].bits,current_bits,sizeof(int) * 16); //write_bit_in_array
		(*table)[*counter].sign_bits = sign_bits_counter;
		(*counter)++;

		return;
	}
	else
	{
		unsigned int local_current_bits[16] = {0};
		memcpy(local_current_bits,current_bits,sizeof(int) * 16);

		move_left(local_current_bits);
		local_current_bits[0] += 1;
		make_table(huffman_tree->right,local_current_bits,counter,table,sign_bits_counter+1);
		local_current_bits[0] -= 1;
	
		make_table(huffman_tree->left,local_current_bits,counter,table,sign_bits_counter+1);
	
		return;
	}
}

//writes bits defined by value and sign_bits in bits_flow
/*void write_bit_char(bits_flow *current,unsigned char value, int sign_bits)
{
	if (sign_bits + current->sign_bits >= sizeof(char)*8)
	{
		unsigned char addition = (8 - current->sign_bits);
		current->buffer_char <<= addition;
		current->buffer_char += (value >> (sign_bits - addition));
		fwrite(&current->buffer_char,1,sizeof(char),current->file);
		value <<= (8 - sign_bits + addition);
		value >>= (8 - sign_bits + addition);
		current->buffer_char = value;
		current->sign_bits = sign_bits - addition;
	}
	else
	{
		current->buffer_char <<= sign_bits;
		current->buffer_char += value;
		current->sign_bits += sign_bits;
	}
}*/

void write_bit_int(bits_flow *current, unsigned int value, int sign_bits)
{
	if (sign_bits + current->sign_bits >= sizeof(int)*8)
	{
		unsigned char addition = (32 - current->sign_bits);
		current->buffer_int <<= addition;
		current->buffer_int += (value >> (sign_bits - addition));
		fwrite(&current->buffer_int,1,sizeof(int),current->file);
		value <<= (32 - sign_bits + addition);
		value >>= (32 - sign_bits + addition);
		current->buffer_int = value;
		current->sign_bits = sign_bits - addition;
	}
	else
	{
		current->buffer_int <<= sign_bits;
		current->buffer_int += value;
		current->sign_bits += sign_bits;
	}
}

void write_long_bits(bits_flow *current, unsigned int value[16], int sign_bits,char c)
{
	int i = 15;
	while (32 * (i+1) - sign_bits > 31)
	{
		i--;
	}
	if (i == 1) 
	{
		printf("stopped at i = %d\n",i);
		printf("the whole value is : %0x%0x\n",value[1],value[0]);
		printf("char is %d\n",c);
	}
	while (i >= 0)
	{
		if (sign_bits > 32 * (i+1))
		{
			write_bit_int(current,value[i],32);
		}
		else
		{
			if (i == 1) printf("writing part of the value  %0x with sign bits %d\n",value[i],32 - (32 * (i+1) - sign_bits));
			write_bit_int(current,value[i],(32 - (32 * (i+1) - sign_bits)));
		}
		i--;
	}
	/*
	int i = 0;
	for (i = 0; i < 16; i++)
	{
		if (sign_bits > 32 * (i+1))
		{
			write_bit_int(current,value[i],32);
		}
		else
		{
			write_bit_int(current,value[i],(32 - (32 * (i+1) - sign_bits)));
			return;
		}
	}*/
	
}

//writes huffman tree into compressed file
void make_hex_huffman(Node *huffman_tree,bits_flow *current)
{
	if ((huffman_tree->right == NULL) && (huffman_tree->left == NULL)) //means the leaf node
	{
		//writing one bit and char itself
		write_bit_int(current,1,1);
		write_bit_int(current,huffman_tree->data.simb,8);
		return;
	}
	else
	{
		//writing 0 and going forward
		write_bit_int(current,0,1);
		make_hex_huffman(huffman_tree->right,current);
		make_hex_huffman(huffman_tree->left,current);
		return;
	}
}

void make_hex_main(Table_elem *table,bits_flow *current)
{
    FILE *input_file = fopen(INPUT_FILE_NAME,"r");
    unsigned char c = 0;
    while (1)
    {
        int rc = fread(&c,sizeof(char),1,input_file);
        if (rc != 1)
        {
            break;
        }
        int i = 0;
        while(c != table[i].simb)
        {
            i++;
        }
        if (c == 'a') printf("a is found\n");
        if (c == 'b') printf("b is found\n");
   		write_long_bits(current,table[i].bits,table[i].sign_bits,c);
     
    }

    //writing the rest of the buffer
    unsigned char addition = 32 - current->sign_bits;
    current->buffer_int <<= addition;
    fwrite(&(current->buffer_int),1,sizeof(int),current->file);
    current->buffer_int = EOF;
    fwrite(&(current->buffer_int),1,sizeof(int),current->file);

    fclose(current->file);
    fclose(input_file);
}

void make_hex(Table_elem *table,Node *huffman_tree, unsigned int number_of_chars, int64_t amount_of_symbols)
{
	FILE *hex_file = fopen(HEX_FILE_NAME,"w");
	fwrite(&number_of_chars,1,sizeof(int),hex_file);
	fwrite(&amount_of_symbols,1,sizeof(int64_t),hex_file);
	//writing huffman tree into the file
	bits_flow current = {.sign_bits = 0, .buffer_int = 0, .file = hex_file};
	printf("inserting tree in the file\n");
	make_hex_huffman(huffman_tree,&current);
	//writing main information in hex file
	printf("inserting main code in the file: \n");
	make_hex_main(table,&current);
	return;
}

void printf_all_table(Table_elem *array)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < 256; i++)
	{
		if (array[i].sign_bits > 32)
		{
			printf("table element %d\n",array[i].simb);
			printf("with sign bits %d\n",array[i].sign_bits);
			printf("bits %0x%0x\n",array[i].bits[1],array[i].bits[0]);

		}
	}
	return ;
}

int main()
{
	unsigned int number_of_chars = 0;
	int64_t amount_of_symbols = 0;
	Node *huffman_tree = make_tree_from_file(INPUT_FILE_NAME,&number_of_chars,&amount_of_symbols); 
	if (NULL == huffman_tree)
	{
		return -1;
	}
	printf("the tree is made \n");
	printf("amount of symbols :%d\n",amount_of_symbols);
	
	//making table
	printf("the number of chars are : %d\n",number_of_chars);
	Table_elem *table = (Table_elem *)calloc(number_of_chars,sizeof(Table_elem));
	int counter = 0;
	unsigned int current_bits[16] = {0};
	make_table(huffman_tree,current_bits,&counter,&table,0);
	printf("the table is made\n");
	printf_all_table(table);
	
	//making hex file
	make_hex(table,huffman_tree,number_of_chars,amount_of_symbols);
	
	destroy_tree(huffman_tree);
	free(table);
	return 0;
}