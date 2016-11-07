#ifndef _INPUT_PARSER_H_
#define _INPUT_PARSER_H_

#include <stdlib.h>
#include <iostream>
#include <vector>

using ERROR_ID = 
	enum ERROR_TYPE
	{
		STRATEGY_ERROR,
		STEPS_ERROR,
		MODE_ERROR
	};

namespace InputParser
{
	void Parse_Argv(int argc, char **argv);
	extern int steps;
	extern std::string matrix_file_name;
	extern std::string mode_name;
	extern std::vector<std::string> strategy_name;
}


#endif