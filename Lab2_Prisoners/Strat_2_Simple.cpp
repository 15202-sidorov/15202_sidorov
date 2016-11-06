#include "Strat_2_Simple.h"

namespace 
{
	//strategy is registrating itself
	Strategy *createStrat_2()
	{
		return new Strategy_Simple_2;
	}

	bool ok = Factory<Strategy,std::string,std::function<Strategy *()>> :: getInstance()->regist3r("Strategy_Simple_2",createStrat_2);
}

Strategy_Simple_2 :: ~Strategy_Simple_2(){ return; } 

void Strategy_Simple_2 :: tell_result(move, move){ return; } 

move Strategy_Simple_2 :: say() const { return Cooperate; }
