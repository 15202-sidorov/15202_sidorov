#ifndef STRATEGY_H
#define STRATEGY_H

typedef
	enum 
	{
		Deny,
		Cooperate
	}move;

class Strategy
{
public:
	virtual move& say() const = 0;
	virtual void  tell_result(const move& ,const move&) = 0;
	virtual void give_points(int) = 0;
	virtual ~Strategy() = 0;
}


#endif