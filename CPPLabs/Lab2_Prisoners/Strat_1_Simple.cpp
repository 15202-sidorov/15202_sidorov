#include "Strat_1_Simple.h"

namespace 
{
	//strategy is registrating itself
	Strategy *createStrat_1()
	{
		return new Strategy_Simple_1;
	}

	bool ok = Factory<Strategy,std::string,std::function<Strategy *()>> :: getInstance()->regist3r("Strategy_Simple_1",createStrat_1);
}

Strategy_Simple_1 :: ~Strategy_Simple_1(){ } 

void Strategy_Simple_1 :: tell_result(move, move,int){ } 

move Strategy_Simple_1 :: say() { return Deny; }


