#include "feild.h"


void Feild::play(int n)
{
	for(int i = 0; i < n; i++)
	{
		play_once();
	}
}

bool Feild::CheckCell(int x, int y)
{
	assert(x >= 0);
	assert(y >= 0);
	assert(cell);
	
	int left = (x-1 < 0 ? width : x-1);
	int right = (x+1 > width ? 0 : x+1);
	int bottom = (y-1 < 0 ? height : y-1);
	int up = (y+1 > height ? 0 : y+1); 

	int count = 0;
	for (int i = left; i <= right; i++)
	{
		for (int j = bottom; j <= up; j++)
		{
			if ((i == x) && (j == y))
			{
				continue;
			}
			if (cell[i*height + j])
			{
				count++;
			}
		}
	}
	
	//return rules[count];
	return 1;
}

void Feild::play_once()
{
	bool *new_cells = new bool[height * width];

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			new_cells[i*height + j] = CheckCell(i,j);
		}
	}

	delete[] cell;
	cell = new_cells;
}

bool Feild::getCellState(int x, int y)
{
	ASSERT_COORDINATES

	return cell[x * height + y];
}

void Feild::setCellState(int x, int y, bool val)
{
	ASSERT_COORDINATES
	cell[x * height + y] = val;
	return;
}


	