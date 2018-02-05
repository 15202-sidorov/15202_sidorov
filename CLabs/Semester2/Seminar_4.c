#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

#define W_size 14
#define N_size 6

#define max(x,y) ((x) > (y) ? (x) : (y))



int value(int w, int n, int w_arr[N_size], int p_arr[N_size], int table[W_size][N_size])
{
	if (table[w][n] != -1)
	{
		return table[w][n];
	}
	if ((n == 0) || (w == 0))
	{
		return (table[w][n] = 0);
	}
	if (w_arr[n] > w)
	{
		return (table[w][n] = value(w,n-1,w_arr,p_arr,table));
	}
	
	int res1 = value(w-w_arr[n],n-1,w_arr,p_arr,table) + p_arr[n];
	int res2 = value(w,n-1,w_arr,p_arr,table);
	return (table[w][n] = max(res1,res2));
}

void value_final(int w, int n, int w_arr[N_size], int p_arr[N_size], int table[W_size][N_size])
{
	if ((n == 0) || (w == 0))
	{
		return;
	}
	int res1 = table[w-w_arr[n]][n-1] + p_arr[n];
	int res2 = table[w][n-1];
	if (res1 > res2)
	{
		value_final(w-w_arr[n],n-1,w_arr,p_arr,table);
		printf("%2d\n",n);
		return;
	}
	else
	{
		value_final(w,n-1,w_arr,p_arr,table);
		return;
	}

}

int main()
{
	int w_arr [N_size] = {0};
	int p_arr [N_size] = {0};

	w_arr[1] = 3; p_arr[1] = 1;
	w_arr[2] = 4; p_arr[2] = 6;
	w_arr[3] = 5; p_arr[3] = 4;
	w_arr[4] = 8; p_arr[4] = 7;
	w_arr[5] = 9; p_arr[5] = 6;

	int i = 0;
	int j = 0;
	int result = 0;
	int table[W_size][N_size];

	for (i = 0; i < N_size; i++)
	{
		for (j = 0; j < W_size; j++)
		{	
			table[j][i] = -1;
		}
	}

	for (i = 0; i < N_size; i++)
	{
		for (j = 0; j < W_size; j++)
		{	
			printf("%2d ",result = value(j,i,w_arr,p_arr,table));
		}
		printf("\n");
	}

	printf("RESULT :%d\n",result);
	printf("THINGS WE ARE TAKING: \n");
	value_final(W_size-1,N_size-1,w_arr,p_arr,table);



	
	return 0;
}