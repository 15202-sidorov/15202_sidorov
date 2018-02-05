#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>

#define HEX_FILE_NAME "hex_file"
#define TARGET_FILE_NAME "target"
#define OUTPUT_FILE_NAME "output"

#define BITS_IN_CHAR sizeof(char) * 8
#define BITS_IN_INT sizeof(int) * 8

/*
	REMARKS
	next bit works right the problem is in getting char or making a tree
*/

typedef
    struct BITSTREAM
    {
        FILE *f;
        unsigned int cur_word; //buffer of bits
        unsigned int cur_bit_id;
        unsigned int count_chars;
    }BitStream;

typedef 
	struct HUFFMAN_TREE
	{
		struct HUFFMAN_TREE *right;
		struct HUFFMAN_TREE *left;
		unsigned char data;
	}Node;


int next_bit(BitStream *bs) // returns 0 or 1 from the bitstream
{
	//in case we read all the buffer
	if (bs->cur_bit_id >= BITS_IN_INT)
	{
		bs->cur_bit_id = 0;
		// reading the next int into the buffer
		fread(&(bs->cur_word),sizeof(int),1,bs->f);
	}
	//returning the current bit
	int result = (bs->cur_word >> (BITS_IN_INT - bs->cur_bit_id - 1)) % 2;
	bs->cur_bit_id++;
	return result;
}

Node *init_node()
{
	Node *result = (Node *)calloc(1,sizeof(Node));
	return result;
}

//reads one byte out of bs
char get_char_from_bs(BitStream *bs)
{
	char result = 0;
	int i = 0;
	for (i = 0; i < BITS_IN_CHAR; i++)
	{
		result <<= 1;
		result += next_bit(bs);
	}
	return result;
}

void print_bits(BitStream bs, int amount)
{
	int i = 0;
	for (i = 0; i < amount; i++)
	{
		printf("%d ",next_bit(&bs));
	}
	printf("\n");
	return;
}

//makes huffman tree from bit stream
Node *make_huffman_tree(BitStream *bs)
{
	if (bs->count_chars <= 0)
	{
		return NULL;
	}
	Node *current_node = init_node();
	while (next_bit(bs) == 1)
	{
		printf("current bit is one, reading the char\n");
		current_node->data = get_char_from_bs(bs);
		printf("the char %c is read\n",current_node->data);
		current_node->right = NULL;
		current_node->left = NULL;
		bs->count_chars--;
		printf("chars are left %d\n",bs->count_chars);
		return current_node;
	} 
	printf("0 is read\n");
	current_node->right = make_huffman_tree(bs);
	current_node->left = make_huffman_tree(bs);
	return current_node;

}

int print_letters_in_file(FILE *output_file,BitStream *bs, Node *Huffman_tree)
{
	while (1)
	{
		if ((Huffman_tree->right == NULL) && (Huffman_tree->left == NULL))
		{
			fprintf(output_file,"%c",Huffman_tree->data);
			return 1;
		}
		if (next_bit(bs) == 1)
		{
			Huffman_tree = Huffman_tree->right;
		}
		else
		{
			Huffman_tree = Huffman_tree->left;
		}
	}
}

//prints the whole tree
void printf_tree(Node *current)
{
	if (current == NULL)
	{
		return;
	}
	else
	{
		if ((current->right == NULL) && (current->left == NULL))
		{
			printf("char is found %c\n",current->data);
			printf("coming back\n");
			return;
		}
		else 
		{
			printf("going right\n");
			printf_tree(current->right);
			printf("going left\n");
			printf_tree(current->left);
			printf("coming back\n");
			return;
		}
	}
}

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

int main()
{
	FILE *bit_file = fopen(HEX_FILE_NAME,"r");
	BitStream current = {0};
	current.f = bit_file;
	int64_t amount_of_symbols = 0;
	//reading the amount of char in the string
	fread(&current.count_chars,1,sizeof(int),bit_file);
	fread(&amount_of_symbols,1,sizeof(int64_t),bit_file);
	printf("Read the amount of chars : %d\n",current.count_chars);
	printf("Read the amount of all chars : %d\n",amount_of_symbols);

	//loading first information
	fread(&current.cur_word,sizeof(int),1,bit_file);
	printf("Here are the bits we're going to get: \n");
	
	//print_bits(current,BITS_IN_INT*2);
	Node *huffman_tree = make_huffman_tree(&current);

	//printf_tree(huffman_tree);

	FILE *output_file = fopen(OUTPUT_FILE_NAME,"w");
	int counter = 0;
	while (counter != amount_of_symbols-1)
	{
		print_letters_in_file(output_file,&current,huffman_tree);
		counter++;
	}
	fclose(output_file);
	printf("done.\n");
	destroy_tree(huffman_tree);	

	fclose(bit_file);
	return 0;
}