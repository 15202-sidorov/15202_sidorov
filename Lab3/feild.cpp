#include "feild.h"

//default value
std::vector<int> Feild::rules_alive = {0,0,1,1,0,0,0,0,0};
std::vector<int> Feild::rules_dead  = {0,0,0,1,0,0,0,0,0};

//always takes rules out of this file
//or sets default
std::string Feild::rules_file_name = "rules.txt";

Feild::Feild(int width_, int height_)
	: width(width_ - 1), height(height_ - 1)
{
	cell = new bool[(width_) * (height_)]();
	get_rules();
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
	if ((x < 0) || (y < 0) || (x > width) || (y > height))
	{
		return 0;
	}
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
				x_around = width;
			}
			if (j < 0)
			{
				y_around = height;
			}

			if (i > width)
			{
				x_around = 0;
			}

			if (j > height)
			{
				y_around = 0;
			}

			if (cell[x_around * (height+1) + y_around])
			{
				count++;
			}
		}
	}
	return count;	
}

bool Feild::CheckCell(int x, int y) const
{
	assert(cell+x*(height+1)+y);
	switch(cell[x*(height+1) + y])
	{
		case false:
			if (!rules_dead[CountLiving(x,y)])
			{
				return false;
			}
		case true:
			if (!rules_alive[CountLiving(x,y)])
			{
				return false;
			}
	}
	return true;
}

void Feild::play_once()
{
	bool *new_cells = new bool[(height+1) * (width+1)]();

	for (int i = 0; i <= width; i++)
	{
		for (int j = 0; j <= height; j++)
		{
			new_cells[i*(height+1) + j] = CheckCell(i,j);
		}
	}

	delete[] cell;
	cell = new_cells;
}

bool Feild::getCellState(int x, int y) const
{
	if ((x < 0) || (y < 0) || (x > width) || (y > height))
	{
		return false;
	}
	return cell[x * (height+1) + y];
}

void Feild::changeCellState(int x, int y)
{
	if ((x < 0) || (y < 0) || (x > width) || (y > height))
	{
		return;
	}
	cell[x * (height+1) + y] = !cell[x * (height+1) + y];
	return;
}

void Feild::clear()
{
	for (int i = 0; i <= width; i++)
	{
		for (int j = 0; j <= height; j++)
		{
			cell[i * (height+1) + j] = 0;
		}
	}
}

bool Feild::get_rules()
{
	std::ifstream rules_file(rules_file_name);
	std::string rule_string;
	
	for (int i = 0; i < 8; i++)
	{
		rules_file >> rules_dead[i];
		if ((rules_dead[i] > 8) || (rules_dead[i] < 0))
		{
			throw -1;
		}
	}

	rules_file >> rule_string;

	for (int i = 0; i < 8; i++)
	{
		rules_file >> rules_alive[i];
		if ((rules_alive[i] > 8) || (rules_alive[i] < 0))
		{
			throw -1;
		}
	}

	rules_file.close();
	return 1;
}

Feild::~Feild()
{
	delete [] cell;
}


	