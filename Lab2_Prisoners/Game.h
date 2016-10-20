#ifndef GAME_H
#define GAME_H

#include "Strategy.h"
#include <iostream>
#include <vector>

typedef
	enum MODE
	{
		TOURNAMENT,
		NORMAL
	} game_mode;

class Game
{
public:
	Game(const Strategy&, const Strategy&, const Strategy&);
	Game() = delete;

	void play();

	~Game();
private:
	std :: vector<vector<vector<int[3]>>> matrix = {}; // define here
	int *count_result(const move& , const move&, const move&);
	game_mode mode;
	Strategy s1;
	Strategy s2;
	Strategy s3;
}


#endif