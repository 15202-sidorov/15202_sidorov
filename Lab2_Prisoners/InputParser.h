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

class InputParser
{
public:	
	static void set_default_tour();
	static void Parse_Argv(int argc, char **argv);
	static std::string get_mode();
	static std::string get_matrix();
	static std::vector<std::string> get_strategies();
	static int get_steps();

private:
	static int steps;
	static std::string matrix_file_name;
	static std::string mode_name;
	static std::vector<std::string> strategy_name;

};

#endif