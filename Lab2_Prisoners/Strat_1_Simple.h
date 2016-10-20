#ifndef STRAT_SIMPLE
#define STRAT_SIMPLE

#include "Strategy.h"

/*
	Stupid strategy, always says DENY
*/

class Strategy_Simple : public Strategy
{
public:
	move& say() const override;
	void  tell_result(const move& ,const move&) override;
	void give_points(int) override;
	~Strategy_Simple() override;
};


#endif