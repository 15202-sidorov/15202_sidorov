#ifndef _FEILD_H_
#define _FEILD_H_

#include <iostream>
#include <vector>
#include <assert.h>

#define ASSERT_COORDINATES \
	assert(x >= 0); \
	assert(y >= 0); \
	assert(x <= width); \
	assert(y <= height);

class Feild
{
public:
	Feild(int width_, int height_)
		: width(width_), height(height_)
	{
		cell = new bool[width * height]();
	};
	
	int getWidth() {return width;};
	int getHeight() {return height;};

	void play(int n);
	bool getCellState(int x, int y);
	void setCellState(int x, int y, bool val);

	~Feild()
	{
		delete [] cell;
	}

private:
	int width;
	int height;
	void play_once();
	bool CheckCell(int x, int y);
	bool *cell;
	//static const bool *rules = {0,1,1,0,0,0,0,0};

};


#endif