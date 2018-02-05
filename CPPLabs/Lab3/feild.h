#ifndef _FEILD_H_
#define _FEILD_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

class Feild
{
public:
	Feild(int width_, int height_);
	int getWidth() const { return width + 1; };
	int getHeight() const { return height + 1; };
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
	
	bool get_rules();
	std::vector<int> rules_alive = {0,0,1,1,0,0,0,0,0};
	std::vector<int> rules_dead  = {0,0,0,1,0,0,0,0,0};
	std::string rules_file_name  = "rules.txt";

};


#endif