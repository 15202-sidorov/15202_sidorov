#ifndef STRAT_SIMPLE_2
#define STRAT_SIMPLE_2

#include "Strategy.h"
#include "Design_Pattern.h"

/*
	Stupid strategy, always says DENY
*/

class Strategy_Simple_2 : public Strategy
{
public:
	move say() const override;
	void  tell_result(move ,move) override;
	~Strategy_Simple_2() override;
};


#endif