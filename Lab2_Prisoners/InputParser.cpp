#include "InputParser.h"

InputParser::InputParser(int argc, char **argv)
	: steps(1), matrix_file_name("default"), 
	mode_name("detailed"), strategy_name({})
{
	int i = 1;
	while(argc > i)
	{
		if (*argv[i] != '-')
		{
			strategy_name.push_back(argv[i]);
			i++;
		}
		else
		{
			break;
		}
	}
		
	if (strategy_name.size() < 3)
	{
		throw STRATEGY_ERROR;
	}
	else if (strategy_name.size() > 3)
	{
		mode_name = "tournament";
	}

	while(argc > i)
	{
		std::string tmp = argv[i];
		if (tmp == "--mode=")
		{
			tmp = argv[++i];
			if ((tmp != "detailed") && (tmp != "fast") && (tmp != "tournament"))
			{
				throw MODE_ERROR;
			}
			mode_name = tmp;
		}
		else if (tmp == "--steps=")
		{	
			tmp = argv[++i];
			for(int j = 0; j < tmp.size(); j++)
			{
				if ((tmp[j] > '9')  || (tmp[j] < '0'))
				{
					throw STEPS_ERROR;
				}
			}
			steps = atoi(argv[i]);
		}
		else if (tmp == "--matrix=")
		{	
			tmp = argv[++i];
			matrix_file_name = tmp;	
		}
		i++;
	}
		
	if (strategy_name.size() < 3)
	{
		throw STRATEGY_ERROR;
	}

	while(argc > i)
	{
		std::string tmp = argv[i];
		if (tmp == "--mode=")
		{
			tmp = argv[++i];
			if ((tmp != "detailed") && (tmp != "fast") && (tmp != "tournament"))
			{
				throw MODE_ERROR;
			}
			mode_name = tmp;
		}
		else if (tmp == "--steps=")
		{	
			tmp = argv[++i];
			for(int j = 0; j < tmp.size(); j++)
			{
				if ((tmp[j] > '9')  || (tmp[j] < '0'))
				{
					throw STEPS_ERROR;
				}	
			}
			steps = atoi(argv[i]);
		}
		else if (tmp == "--matrix=")
		{	
			tmp = argv[++i];
			matrix_file_name = tmp;	
		}
		i++;
	}
};

