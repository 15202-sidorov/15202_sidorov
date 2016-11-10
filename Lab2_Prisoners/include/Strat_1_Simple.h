#ifndef STRAT_SIMPLE_1
#define STRAT_SIMPLE_1

#include "Strategy.h"
#include "Design_Pattern.h"

/*
	Stupid strategy, always says DENY
*/

class Strategy_Simple_1 : public Strategy
{
public:
	move say() const override;
	void  tell_result(move ,move) override;
	//void give_name() override;
	~Strategy_Simple_1() override;

};


#endif