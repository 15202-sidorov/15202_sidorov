#include "InputParser.h"

int InputParser::steps = 1;
std::string InputParser::matrix_file_name = "default";
std::string InputParser::mode_name = "detailed";
std::vector<std::string> InputParser::strategy_name = {};

void InputParser::Parse_Argv(int argc, char **argv)
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

void InputParser::set_default_tour()
{
	mode_name = "tournament";
}

std::string InputParser::get_mode() { return mode_name; };
std::string InputParser::get_matrix() { return matrix_file_name ; };
std::vector<std::string> InputParser::get_strategies() { return strategy_name; };
int InputParser::get_steps() { return steps; };