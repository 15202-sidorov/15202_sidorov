#include <stdio.h>
#include <stdlib.h>
//Done
//https://github.com/iefremov/tundra-x/blob/master/tundra/website/1st-malloc.md

void *realoc(void *ptr, int size, int new_size) // sizeof(char) = 1byte;!!
{
	char *new_arr = (char *)malloc(new_size); // creating a new array with more memory
	int i;
	
	char *ptr2 = (char *)ptr; // разлиновываем
	
	for (i = 0; i < size; i++)
		*(ptr2+i) =  'a';

	for (i = 0; i < new_size; i++)
		printf("%c\n",*(new_arr+i));
	
	for (i = 0; i < new_size; i++)
		*(new_arr+i) = *(ptr2+i);



	
	return (void *)new_arr;
}

void swap(int *x, int *y) 
{
	int r;
	r = *x;
	*x = *y;
	*y = r;
}

void malloc_func()
{
	int size,i,num;
	size = 3;
	//int *arr = (int *) malloc(size*sizeof(int));
	int *arr = (int *) calloc(size,sizeof(int));
		for(i = 0; i < size; i++)
			printf("%d\n",*(arr+i));


	free(arr);
}

void how_much()
{
	long long int i,size,mem;
	mem = 1;
	int *arr;

	while(1)
	{
		arr = (int *)calloc(mem,sizeof(int)); // выделяем память 
		if (arr == NULL) // проверка если не согли выделить
		{
			printf("No memory");
			return -1;		
		}
		printf("%d\n",mem*sizeof(int)); // показываем сколько выделили
		mem *= 2; // умножаем количество памяти на 2
		getchar(); // нажимаем любую кнопку
		free(arr);
	}
	

}


int main()
{
	printf("%d\n",sizeof(int));
	
	return 0;

}