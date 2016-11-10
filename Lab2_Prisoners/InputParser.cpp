#include "include/InputParser.h"

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
		
		try
		{
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
		}
		catch(ERROR_ID err)
		{
			switch(err)
			{
				case STEPS_ERROR:
				{
					std::cerr << "Steps error,abort" << std::endl;
					exit(-1);
				}
				case STRATEGY_ERROR:
				{
					std::cerr << "Not enough strategies,abort" << std::endl;
					exit(-1);
				}
				case MODE_ERROR:
				{
					std::cerr << "Wrong mode,abort" << std::endl;
					exit(-1);
				}
			}
		}	

		if (strategy_name.size() > 3)
		{
			mode_name = "tournament";
		}
};
