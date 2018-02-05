#include <stdio.h>
#include <stdlib.h>

#define AMOUNT 6
#define NOT_USED 2

char **read_the_graf()
{
	FILE *input_file = fopen("Seminar_1.txt","r");
	char **graf = (char **)calloc(AMOUNT,sizeof(char *));
	int i = 0;
	for (i = 0; i < AMOUNT; i++)
	{
		graf[i] = (char *)calloc(AMOUNT,sizeof(char));
		int j = 0;
		for (j = 0; j < AMOUNT; j++)
		{
			fscanf(input_file,"%d",(int *)(graf[i]+j));
			fgetc(input_file);
			printf("%d ",graf[i][j]);
		}
		fscanf(input_file,"\n");
		printf("\n");
	}
	fclose(input_file);
	return graf;
}

void printf_graf(char **graf)
{
	int i = 0, j = 0;
	for (i = 0; i < AMOUNT; i++)
	{
		for (j = 0; j < AMOUNT; j++)
		{
			printf("%d ",graf[i][j]);
		}
		printf("\n");
	}
	return;
}

void free_graf(char **graf)
{
	int i = 0,j = 0;
	for (i = 0; i < AMOUNT; i++)
	{
		free(graf[i]);
	}
	free(graf);
	return;
}

void mark_the_element(char **graf,int i)
{
	int j = 0;
	for (j = 0; j < AMOUNT; j++)
	{
		if (graf[j][i] != NOT_USED)
		{
			graf[j][i] = 0;
		}
		graf[i][j] = NOT_USED;
	}
	
	return;
}

int find_and_delete(char **graf)
{
	int j = 0;
	int i = 0;
	for (i = 0; i < AMOUNT; i++)
	{
		int flag = 0;
		if (NOT_USED == graf[i][0])
		{
			continue;
		}
		for (j = 0; j < AMOUNT; j++)
		{
			if (NOT_USED == graf[i][j])
			{
				continue;
			}
			else if (1 == graf[i][j])
			{
				flag = 1;
				break;
			}
		}
		if (0 == flag)
		{
			mark_the_element(graf,i);
			return i;
		}
	}
	return -1;
}

int main()
{
	
	char **graf = read_the_graf();
	
	int i = 0;

	for (i = 0; i < AMOUNT; i++)
	{
		int found = find_and_delete(graf);
		
		if (-1 == found)
		{
			fprintf(stderr,"%s\n","Circled graf\n");
			break;
		}
		else 
		{
			printf("%d\n",found);
		}
		printf_graf(graf);
		printf("\n");
	}

	free_graf(graf);
	return 0;
}