#include "Game_Tournament.h"

void Game_Tournament :: play_once(Strategy *s1, Strategy *s2, Strategy *s3, int i, int j, int k)
{
	move m1 = s1->say();
	move m2 = s2->say();
	move m3 = s3->say();

	std::vector<int> result_tmp = count_result(m1,m2,m3);

	result[i] += result_tmp[0];
	result[j] += result_tmp[1];
	result[k] += result_tmp[2];

	s1->tell_result(m2,m3,result_tmp[0]);
	s2->tell_result(m1,m3,result_tmp[1]);
	s3->tell_result(m1,m2,result_tmp[2]);

	return ;
}

void Game_Tournament :: play()
{
	for(int i = 0; i < all_strat.size(); i++)
	{
		for(int j = i+1; j < all_strat.size(); j++)
		{
			for (int k = j+1; k < all_strat.size(); k++)
			{
				play_once(all_strat[i].get(),all_strat[j].get(),all_strat[k].get(),i,j,k);
				std::cout << "Play :" << i << " " << j << " " << k << std::endl;
			}
		}
	}
	
	std::cout << "Resulted points: " ;
	for (int n : result)
	{
		std::cout << n << " " ;
	}
	std::cout << std::endl;
}