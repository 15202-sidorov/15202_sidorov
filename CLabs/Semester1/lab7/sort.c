#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sort.h"

#define UNALLOWED_VALUE -1

static int *merge(int *left,int *right,int size_left,int size_right) // merge two symbols
{
	int *result = (int *)calloc(size_left+size_right,sizeof(int));
	int i = 0; 
	int j = 0;
	int count = 0;
	while((i < size_left) && (j < size_right))
	{
		if (left[i] >= right[j])
		{
			result[count] = right[j];
			j++;
		}
		else
		{
			result[count] = left[i];
			i++;
		}
		count++;
	}
	while(i < size_left)
	{
		result[count] = left[i];
		count++;
		i++;
	}
	while(j < size_right)
	{
		result[count] = right[j];
		count++;
		j++;
	}
	return result;
}

int *merge_sort(int *arr,int size) // the sort of a file of allowed size
{
	assert(arr);
	if (1 == size)
	{
		return arr;
	}
	int *tmp = (int *)calloc(size,sizeof(int));
	int i = 0;
	for (i = 0; i < size; i++) // in order to be able to make free(left,right) without losing information
	{
		tmp[i] = arr[i];
	}
	int *left = merge_sort(tmp,size/2);
	int *right = merge_sort(tmp+size/2,size-size/2);
	int *result = merge(left,right,size/2,size-size/2);
	free(tmp);
	free(left);
	free(right);

	return result;
}

void merge_sort_main(FILE **arr_file,int files_count)
{
	//open files of an allowed size are coming into function 
	assert(arr_file);
	FILE *result = fopen("result.txt","w");
	int i = 0;
	int *arr_with_min = (int *)calloc(files_count,sizeof(int));

	int min = MAX_VAL;
	int min_index = 0;
	for (i = 0; i < files_count; i++)
	{
		fscanf(arr_file[i],"%d ",arr_with_min+i);
		if (arr_with_min[i] < min)
		{
			min = arr_with_min[i];
			min_index = i;
		}
	}
	fprintf(result,"%d ",min);
		

	int count_closed_files = 0;
	while (1)
	{
		int rc = fscanf(arr_file[min_index],"%d ",arr_with_min + min_index); //adding the new element
		if (-1 == rc)
		{
			count_closed_files++;
			arr_with_min[min_index] = UNALLOWED_VALUE;
		}
		if (count_closed_files == files_count)
		{
			break;
		}
		min = MAX_VAL;
		for (i = 0; i < files_count; i++)
		{
			if ((arr_with_min[i] < min) && (arr_with_min[i] != UNALLOWED_VALUE))
			{
				min = arr_with_min[i];
				min_index = i;
			}
		}
		fprintf(result,"%d ",min);
	}

	free(arr_with_min);
	fclose(result);
	return;
}
