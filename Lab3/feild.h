#ifndef _FEILD_H_
#define _FEILD_H_

#include <iostream>
#include <vector>
#include <assert.h>

class Feild
{
public:
	Feild(int width_, int height_);
	int getWidth() const {return width;};
	int getHeight() const {return height;};
	bool getCellState(int x, int y) const;
	
	void play_once();
	void play(int n);
	void changeCellState(int x, int y);
	void clear();


	~Feild();
private:
	int width;
	int height;
	int CountLiving(int x, int y) const;
	bool CheckCell(int x, int y) const;
	bool *cell;
	static std::vector<int> rules;

};


#endif