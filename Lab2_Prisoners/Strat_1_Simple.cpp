#include "Strat_1_Simple.h"


namespace 
{
	Strategy *createStrat_1()
	{
		return new Strategy_Simple;
	}

	bool ok = Factory :: GetInstance()->regist3r("Strategy_Simple",createStrat_1);
}

Strategy_Simple :: ~Strategy_Simple()
{
	std :: cout << "Distruct this S1!" << std :: endl;
} 

void Strategy_Simple :: tell_result(const move& const move&)
{
	return;
} 

move& Strategy_Simple :: say() const
{
	return Deny;
}

void Strategy_Simple :: give_points(int)
{
	return ;
}