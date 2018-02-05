#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sort.h"

#define ALLOWED_MEM 20 //bytes, 256 int digits
#define GEN_NUM 1
#define SIZE_OF_DATA 4

static void generate_digits(char *file_name)
{
	FILE *input_file = fopen(file_name,"w");
	int i = 0;
	for (i = 0; i < GEN_NUM; i++)
	{
		fprintf(input_file,"%d ",rand() % MAX_VAL);
	}
	fclose(input_file);
	return;
}

static char *gen_name(int i)
{
	char *file_name = (char *)calloc(GEN_NUM*SIZE_OF_DATA/ALLOWED_MEM,sizeof(char));
	itoa(i,file_name,10);
	int length = strlen(file_name);
	char *str = (char *)calloc(length+4,sizeof(char));
	memcpy(str,file_name,length);
	free(file_name);
	str[length] = '.';
	str[length+1] = 't';
	str[length+2] = 'x';
	str[length+3] = 't';
	str[length+4] = '\0';
	return str;
}

int pars_into_sorted_files(FILE *main_file,FILE **arr_file)
{
	assert(main_file);
	assert(arr_file);
	int count = 0;
	while(1)
    {
    	//считываем из main file достаточно инфы и сортируем in arr
    	int consumed_mem = 0;
    	char c = 0;
    	int *arr_int = (int *)calloc(ALLOWED_MEM,sizeof(int));
    	int size = 0;
    	while (consumed_mem < ALLOWED_MEM)
    	{
    		int rc = fscanf(main_file,"%d ",arr_int+size);
    		if (-1 == rc)
    		{
    			break;
    		}
    		size++;
			consumed_mem += SIZE_OF_DATA;
		}
		if (consumed_mem == 0)
		{
			break;
		}
		arr_int = merge_sort(arr_int,size);
		if (c == EOF)
		{
			break;
		}
    	
    	//создаем новый файл
    	char *file_name = gen_name(count);
    	arr_file[count] = fopen(file_name,"w");
    	
    	//записываем отсортированный массив
    	int i = 0;
    	for (i = 0; i < size; i++)
    	{
    		fprintf(arr_file[count],"%d ",arr_int[i]);
    	}
    	
    	//close file
		fclose(arr_file[count]);
		count++;
		free(file_name);
    	free(arr_int);
    }
 
    return count;

}

char **remember_file_names(int files_count)
{
	char **arr = (char **)calloc(files_count,sizeof(char *));
	int i = 0;
	for (i = 0; i < files_count; i++)
	{
		arr[i] = gen_name(i);
	}
	return arr;
}

void open_files(FILE **arr_file,char **file_names,int files_count)
{
	int i = 0;
	for (i = 0; i < files_count; i++)
	{
		arr_file[i] = fopen(file_names[i],"r");
	}
}

void close_files(FILE **arr_file,char **file_names,int files_count)
{
	int i = 0;
	for (i = 0; i < files_count; i++)
	{
		fclose(arr_file[i]);
		remove(file_names[i]);
		free(file_names[i]);
	}
	free(file_names);

}

int main(int argc, char **argv)
{
	generate_digits("target.txt");
	FILE *main_file = fopen("target.txt","r");	
	FILE **arr_file = (FILE **)calloc(GEN_NUM*SIZE_OF_DATA/ALLOWED_MEM,sizeof(FILE *));

	int files_count = pars_into_sorted_files(main_file,arr_file);
	char **file_names = remember_file_names(files_count);
	open_files(arr_file,file_names,files_count);
	merge_sort_main(arr_file,files_count);
	close_files(arr_file,file_names,files_count);


	fclose(main_file);
	
		
	return 0;
}