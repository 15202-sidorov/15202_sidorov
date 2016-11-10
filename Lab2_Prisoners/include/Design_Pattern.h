#ifndef _DESIGN_PATTERN_
#define _DESIGN_PATTERN_

#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <typeinfo>
#include <functional>

template<
	class AbstractProduct,
	typename IdentiferType,
	typename ProductCreator
>
class Factory
{
public:
	Factory(const Factory&) = delete;
	Factory& operator = (const Factory&) = delete;

	static Factory *getInstance()
	{
		static Factory f;
		return &f;
	}

	AbstractProduct *create(IdentiferType id)
	{
		AbstractProduct *result = nullptr;
		try
		{
			result = create_functions.at(id)();
		}
		catch (const std::out_of_range& oor) 
		{
   			std::cerr << "Out of Range error: " << oor.what() << std::endl;

   			exit(-1);
  		}
		return result;
	}

	bool regist3r(IdentiferType id,ProductCreator constructor)
	{
		create_functions[id] = constructor;
		return true;
	}

private:
	Factory(){};
	std::unordered_map<IdentiferType,ProductCreator> create_functions;


};





#endif