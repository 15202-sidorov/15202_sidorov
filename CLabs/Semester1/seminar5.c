#include <stdio.h>
#include <stdlib.h>

// http://pastebin.com/GyASzTrH

void swap (void *a, void *b, int size) // changing the element of a set type
{
	char r;
	char *r1;
	char *r2;
	int i;

	r1 = (char *)a;
	r2 = (char *)b;

	for (i = 0; i < size; i++)
	{
		r = r1[i];
		r1[i] = r2[i];
		r2[i] = r;
	}	

}


int int_cmp(void * a, void * b) 
{
	int *ai = (int *)a;
	int *bi = (int *)b;
	if ((*ai) < (*bi)) return 1;
	else return 0;
}

int double_cmp(void * a, void * b) 
{
	double *ai = (double *)a;
	double *bi = (double *)b;
	if (*ai < *bi) return 1;
	else return 0;     
}



void bubble_sort(void *arr,
					int arr_size, // количство элементов массива
					int element_size, // размер элементов массива
					int (*cmp)(void *a, void *b) // функция сравнения
				)
{
	int i =0 ,j = 0,k = 0;
	
	char **arr_char = (char **)calloc(arr_size,sizeof(char *)); // побайтово разлиновали void *
	for (i = 0; i < arr_size; i++)
	{
		
		arr_char[i] = (char *)(arr) + i*element_size;
	}	
		
	for (i = 1; i < arr_size; i++)
	{
		
		k = i;
		j = i-1;
		while ((*cmp)(arr_char[k],arr_char[j]))
		{
			swap(arr_char[j],arr_char[k],element_size);
			k--;
			j--;
			if (k == 0) break;
		}
	}
	

}

int max(void *arr,
		int arr_size,
		int element_size,
		int (*cmp)(void *,void *)
	)
{
	int i = 0;
	int m = 0;
	char *p = (char *)arr;
	for (i = 1; i < arr_size; i++)
	{
		if (cmp(p + m*element_size,p + i*element_size))
		{
			m = i;	
		}
	}
	return m;

}


int main(int argc, char **argv)
{
	int i = 0;
	int arr[8] = {4,2,4,3,73,5,4,1};
	int m = 0;
	for (i = 0; i < 8; i++)
		{
			printf("%d\n",arr[i]);
		}
	
	

	m = max(arr,8,sizeof(int),int_cmp);
	printf("%d\n",m);
	
	
	return 0;
}