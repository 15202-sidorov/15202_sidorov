#ifndef _GAME_DETAILED_H_
#define _GAME_DETAILED_H_

#include "Game.h"

class Game_Detailed: public Game
{
public:
	Game_Detailed(std::vector<Strategy*>, int, Matrix_T&);
	Game_Detailed() = delete;

	void play() override;
private:
	const int amount_of_steps;
	std::vector<Strategy *> all_strat;
	
	std::vector<int> result = {0,0,0};
	std::vector<int> play_once();
};


#endif