#include "feild.h"

#define ASSERT_COORDINATES \
	assert(x >= 0); \
	assert(y >= 0); \
	assert(x <= width); \
	assert(y <= height);

std::vector<int> Feild::rules = {0,0,1,1,1,0,0,0};

Feild::Feild(int width_, int height_)
	: width(width_), height(height_)
{
	cell = new bool[width * height]();
};
	
void Feild::play(int n)
{
	for(int i = 0; i < n; i++)
	{
		play_once();
	}
}

int Feild::CountLiving(int x, int y) const
{
	ASSERT_COORDINATES
	assert(cell);
	
	int count = 0;
	int x_around = 0;
	int y_around = 0;
	for (int i = x-1; i <= x+1; i++)
	{
		for (int j = y-1; j <= y+1; j++)
		{
			x_around = i;
			y_around = j;
			if ((i == x) && (j == y))
			{
				continue;
			}
			if (i < 0)
			{
				x_around = width - 1;
			}
			if (j < 0)
			{
				y_around = height -1 ;
			}

			if (i > width -1 )
			{
				x_around = 0;
			}

			if (j > height -1 )
			{
				y_around = 0;
			}

			if (cell[x_around * height + y_around])
			{
				count++;
			}
		}
	}
	return count;	
}

bool Feild::CheckCell(int x, int y) const
{
	assert(cell+x*height+y);
	switch(cell[x * height + y])
	{
		case false:
			if (CountLiving(x,y) == 3)
			{
				return true;
			}
			return false;
		case true:
			if ((CountLiving(x,y) != 3) && (CountLiving(x,y) != 2))
			{
				return false;
			}
			return true;
	}
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

bool Feild::getCellState(int x, int y) const
{
	ASSERT_COORDINATES
	return cell[x * height + y];
}

void Feild::changeCellState(int x, int y)
{
	ASSERT_COORDINATES
	cell[x * height + y] = !cell[x * height + y];
	return;
}

void Feild::clear()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			cell[i * height + j] = 0;
		}
	}
}

Feild::~Feild()
{
	delete [] cell;
}


	