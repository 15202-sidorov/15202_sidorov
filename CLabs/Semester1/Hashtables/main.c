#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "hashtable.h"
#include "inf_s.h"

static void printf_HT(HT *ht)
{
	int i = 0;
	for (i = 0; i < ht->size; i++)
	{
		printf("%d: %d\n",i,(ht->data+i)->arr[0]);
	}

	return;
}

int main(int argc, char **argv)
{
	FILE *input_file = fopen(argv[1],"r");
	if (NULL == input_file)
	{
		fprintf(stderr,"NO FILE FOUND",argv[0]);
		return 0;
	}
	
	int d1 = 0, d2 = 0;
	inf_s name;
	HT *ht = create_HT(START_SIZE_HT);
	while(1)
	{
		init_s(&name);
		get_inf_s_from_file(&name,input_file);
		int rc = fscanf(input_file,"%d %d\n",&d1,&d2);
		if ((rc < 2) && (rc != -1))
		{
			fprintf(stderr,"NOT ENOUGH OF CHARACHTERISTICS in the name %s\n",name.s,argv[1]);
			destroy_HT(ht);
			fclose(input_file);
			free(name.s);
			return;
		}
		if (-1 == rc)
		{
			break;
		}
		insert(ht,name,d1,d2);
	}
	fclose(input_file);
	
	printf_HT(ht);
	while(1)
	{
		init_s(&name);
		get_inf_s_std(&name);
		
		int *answer = find(ht,name);
		if (NULL == answer)
		{
			fprintf(stderr,"The name is not in the table\n",argv[1]);
			continue;
		}
		printf("%d %d\n",answer[0],answer[1]);
		free(name.s);
	}
	destroy_HT(ht);
	
	
	return 0;
}