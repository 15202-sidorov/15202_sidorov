#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <unordered_map>
#include "Strategy.h"
#include <iostream>

class Factory
{
public:

	typedef Strategy *(*creator_func)();
	/*
		Cинглтон мейерса
		т.е гарантирует что в приложении будет единственный экземпляр класса 
		с глобальной точкой доступа
	*/
	static Factory *getInstance()
	{
		/*
			Defines that before program
			so it will always return one adress
		*/
		static Factory f;
		return &f;
	}
	/*
		Deleting copy functions for the sake of upwards
	*/
	Factory(const Factory&) = delete;
	Factory& operator = (const Factory&) = delete;

	/*
		The function makes new Strategy
		Should give it function and id
		Id will mean what product do you wanna make 
	*/
	Strategy *create(const std :: string& id)
	{
		
		return creatorz.at(id)();
	}
	/*
		Registers object in factory
	*/
	bool regist3r(const std :: string& id,
				  const creator_func& creator)
	{
		creatorz[id] = creator;
		return true;
	}
private:
	Factory() {};
	std :: unordered_map <std :: string, creator_func> creatorz;

};

#endif