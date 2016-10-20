#include "Game.h"


Game :: Game(Strategy& s1_, Strategy& s2_, Strategy& s3_)
{
	s1 = s1_;
	s2 = s2_;
	s3 = s3_;
	return;
}


void Game :: play()
{
	move m1 = s1.say();
	move m2 = s2.say();
	move m3 = s3.say();

	int *results = count_result(m1,m2,m3);

	s1.tell_results(m2,m3);
	s1.give_points(results[0]);
	
	s2.tell_results(m1,m3);
	s2.give_points(results[1]);
	
	s3.tell_results(m1,m2);
	s3.give_points(results[2]);


	return;
}

int *Game :: count_result(const move& m1,const move& m2, const move& m3)
{
	//using matrix here
	return matrix[m1][m2][m3];
}
