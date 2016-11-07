#ifndef STRATEGY_H
#define STRATEGY_H

using move = 
	enum MOVE
	{
		Deny,
		Cooperate
	};

class Strategy
{
public:
	virtual move say() const = 0;
	virtual void  tell_result(move,move) = 0;
	//virtual void give_name() = 0;
	virtual ~Strategy(){};
/*
protected:
	Strategy(){};
*/
};


#endif