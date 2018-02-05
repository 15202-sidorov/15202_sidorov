#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "trees.h"
#include "inf_s.h"

#define STR_LEN_MAX 30
#define ASCI 26
#define MAX_VAL 100


static char *gen_rand_name()
{
	char *str = NULL;
	int length = rand() % STR_LEN_MAX + 1;
	int i = 0;
	str = (char *)calloc(length+1,sizeof(char));
	for (i = 0; i < length; i++)
	{
		str[i] = (rand() % ASCI) + 'A';
	}
	str[length] = '\0';
	return str;

}

static void generate_inf_names(FILE *input_file, int num)
{
	assert(input_file);
	int i = 0;
	for (i = 0; i < num; i++)
	{
		char *str = gen_rand_name();
		fprintf(input_file,"%s ",str);
		fprintf(input_file,"%d %d\n",rand() % MAX_VAL,rand() % MAX_VAL);
		free(str);
	}
	
	return;
}

int main(int argc, char **argv)
{
	FILE *input_file = fopen(argv[1],"w");
	if (NULL == input_file)
	{
		fprintf(stderr,"NO FILE FOUND",argv[0]);
		return 0;
	}
	generate_inf_names(input_file,20000);
	fclose(input_file);
	input_file = fopen(argv[1],"r");
	
	int d1 = 0, d2 = 0;
	tree *root = NULL;
	inf_s name;
	while(1)
	{
		init_s(&name);
		get_inf_s_from_file(&name,input_file);
		int rc = fscanf(input_file,"%d %d\n",&d1,&d2);
		if ((rc < 2) && (rc != -1))
		{
			fprintf(stderr,"NOT ENOUGH OF CHARACHTERISTICS in the name %s\n",name.s,argv[1]);
			free(name.s);
			return;
		}
		if (-1 == rc)
		{
			break;
		}
		root = insert_in_tree(root,name,d1,d2);
		printf("HEIGHT: %d\n",height(root));
		printf("BALANCE: %d\n",count_balance(root));
	}
	fclose(input_file);
	
	while(1)
	{
		init_s(&name);
		get_inf_s_std(&name);
		
		int *answer = find_in_tree(root,name);
		if (NULL == answer)
		{
			fprintf(stderr,"The name is not in the table\n",argv[1]);
			continue;
		}
		printf("%d %d\n",answer[0],answer[1]);
		free(name.s);
	}

	root = destroy_tree(root);
	fclose(input_file);
	return 0;
}