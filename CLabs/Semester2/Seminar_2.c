#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 8
#define WIDTH 8
#define START_X 0
#define START_Y 0

#define abs(x) (((x) < 0) ? (-x) : (x))

enum STATE
{
	GO_BACK,
	FOUND
};

void printf_feild(int feild[LENGTH][WIDTH])
{
	int i = 0;
	int j = 0;
	for (i = 0; i < LENGTH; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			printf("%2d ",feild[i][j]);
		}
		printf("\n");
	}
}

int count_possible_moves(int feild[LENGTH][WIDTH], int possible_moves[8][2], int i, int j)
{
	int sum = 0;
	int k = 0;
	for (k = 1; k < 8; k++)
	{
		int x = i + possible_moves[k][0];
		int y = j + possible_moves[k][1];
		if ((feild[x][y] == 1) || (x >= LENGTH) || (y >= WIDTH) || (x < 0) || (y < 0))
		{
			sum++;
		}
	}

	return sum;
}

int findmax(int around_elements[8])
{
	int max = -1;
	int i = 0;
	int max_index = -1;
	for (i = 0; i < 8; i++)
	{
		if (around_elements[i] > max)
		{
			max = around_elements[i];
			max_index = i;
		}
	}
	printf("max = %d\n", max);
	if (max_index != -1) around_elements[max_index] = -1;
	return max_index;
}

enum STATE make_move(int feild[LENGTH][WIDTH], int i, int j, int counter)
{
	printf_feild(feild);
	if (counter == WIDTH * LENGTH - 1)
	{
		feild[i][j] = counter;
		return FOUND;
	}
	
	if ((feild[i][j] == 1) ||(i >= LENGTH) || (j >= WIDTH) || (i < 0) || (j < 0))
	{
		return GO_BACK;
	}
	int possible_moves[8][2] = {					//all possible moves
									{-1, -2}, {-2, -1}, {-2,  1}, { 1, -2},
									{-1,  2}, { 2, -1}, { 1,  2}, { 2,  1} 
								};
	int k = 0;
	int around_elements[8] = {0};
	int flag = 0;
	for (k = 1; k < 8; k++)
	{
		int x = i + possible_moves[k][0];
		int y = j + possible_moves[k][1];
		if ((x >= LENGTH) || (y >= WIDTH) || (x < 0) || (y < 0))
		{
			around_elements[k] = -1;
			continue;
		}
		else if (feild[x][y] == 1)
		{
			around_elements[k] = -1;
			continue;
		}
		around_elements[k] = count_possible_moves(feild,possible_moves,x,y);
	}
	counter++;
	k = findmax(around_elements);
	while (k != -1)
	{
		feild[i][j] = 1;
		if (make_move(feild,i + possible_moves[k][0],j + possible_moves[k][1],counter) == FOUND)
		{
			feild[i][j] = counter;
			return FOUND;
		}
		k = findmax(around_elements);
	}
	feild[i][j] = 0;
	return GO_BACK;
}

int main()
{
	int feild[LENGTH][WIDTH] = {0};
	if (make_move(feild,START_X,START_Y,0) == FOUND)
	{
		printf("FOUND\n");
		printf_feild(feild);
	}
	else 
	{
		printf("NOT FOUND\n");
	}

	return 0;
}