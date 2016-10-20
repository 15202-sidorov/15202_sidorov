#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <unrodered_map>

class Factory
{
public:

	typedef Strategy& (*creator_func)();
	/*
		Cинглтон мейерса
		т.е гарантирует что в приложении будет единственный экземпляр класса 
		с глобальной точкой доступа
	*/
	static Factory *getInstance()
	{
		/*
			Defines that before program
			so will always return one adress
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
	Strategy *create(const std :: string& id
					const creator_func& creator)
	{
		creatorz[id] = creator;
		return true;
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
	Factory() = delete;
	std :: unrodered_map <std :: string, creator_t> creatorz;

};