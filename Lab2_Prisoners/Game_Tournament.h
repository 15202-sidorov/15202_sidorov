#ifndef _GAME_TOURNAMENT_H_
#define _GAME_TOURNAMENT_H_

#include "Game.h"

class Game_Tournament: public Game
{
public:
	Game_Tournament(std::vector<Strategy *> ,int ,Matrix_T&) ;
	Game_Tournament() = delete;
	void play() override;
private:
	const std::vector<Strategy *> all_strat;
	const int amount_of_steps;

	void play_once(Strategy *,Strategy *,Strategy *,int,int,int);

	std::vector<int> result;

};


#endif