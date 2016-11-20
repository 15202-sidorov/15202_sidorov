#include "Game_Not_Detailed.h"
#include <assert.h>

std::vector<int> Game_Not_Detailed :: play_once()
{
	assert(all_strat.size() == 3);
	move m1 = all_strat[0]->say();
	move m2 = all_strat[1]->say();
	move m3 = all_strat[2]->say();

	std::vector<int> result_tmp = count_result(m1,m2,m3);

	for (int i = 0; i < result.size(); i++)
	{
		result[i] += result_tmp[i];
	}

	all_strat[0]->tell_result(m2,m3,result_tmp[0]);
	all_strat[1]->tell_result(m1,m3,result_tmp[1]);
	all_strat[2]->tell_result(m1,m2,result_tmp[2]);

	return result_tmp;
}

void Game_Not_Detailed :: play()
{
	for (int i = 0; i < amount_of_steps; i++)
	{	
		play_once();
	}

	std::cout << "Resulted points: " << result[0] << " " << result[1] << " " << result[2] << std::endl;

	return;
}
