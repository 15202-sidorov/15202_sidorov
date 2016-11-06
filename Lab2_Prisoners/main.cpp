
#include "InputParser.h"
#include "Game_Tournament.h"
#include "Game_Detailed.h"
#include "Game_Not_Detailed.h"
#include "Strat_1_Simple.h"
#include "Strat_2_Simple.h"
#include "Design_Pattern.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>


//STRATEGIES!
//how do we define whether to use default matrix??


void GetParameters(int argc,char **argv)
{
	try
	{
		InputParser::Parse_Argv(argc,argv);
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
				std::cerr << "Not enough strategies, abort" << std::endl;
				exit(-1);
			}
			case MODE_ERROR:
			{
				std::cerr << "Wrong mode,abort" << std::endl;
				exit(-1);
			}
		}
	}

	if (InputParser::get_strategies().size() > 3)
	{
		InputParser::set_default_tour();
	}

	return ;
}

Matrix_T ReadMatrix(const std::string& matrix_file_name)
{
	std::ifstream file;
	file.open(matrix_file_name);
	if (!file.is_open())
	{
		std::cout << "Can't find file" << std::endl;
		exit(-1);
	}

	Matrix_T result;
	result.push_back({
						{
							 { 
							 	{0,0,0} 
							 }, 
							 { 
							 	{0,0,0} 
							 } 
						},
						{
							 { 
							 	{0,0,0} 
							 }, 
							 { 
							 	{0,0,0} 
							 } 
						},

					});
	result.push_back({
						{
							 { 
							 	{0,0,0} 
							 }, 
							 { 
							 	{0,0,0} 
							 } 
						},
						{
							 { 
							 	{0,0,0} 
							 }, 
							 { 
							 	{0,0,0} 
							 } 
						},

					});
	std::vector<int> tmp = {0,0,0};
	for (int i = 0; i < 8; i++)
	{
	    int i1 = 0,i2 = 0,i3 = 0;
		file >> i1 >> i2 >> i3;
		file >> tmp[0] >> tmp[1] >> tmp[2];
		if (file.eof())
		{
			std::cerr << "Not enough matrix" << std::endl;
			exit(-1);
		}
		result[i1][i2][i3] = tmp;
	}

	file.close();
	return result;
}

void PlayGame(Matrix_T& matrix_from_file)
{
	Factory<Strategy,std::string,std::function<Strategy *()>> *f =
	Factory<Strategy,std::string,std::function<Strategy *()>> :: getInstance();

	std::vector<Strategy *> all_strategies;
	for(std::string name : InputParser::get_strategies())
	{
		all_strategies.push_back(f -> create(name));
	}
	
	if (InputParser::get_mode() == "detailed")
	{
		Game_Detailed drive(all_strategies,
						    InputParser::get_steps(),
						    matrix_from_file);
		drive.play();
	}
	else if (InputParser::get_mode() == "fast")
	{
		Game_Not_Detailed drive(all_strategies,
						  		InputParser::get_steps(),
						  		matrix_from_file);
		drive.play();
	}
	else if (InputParser::get_mode() == "tournament")
	{
		Game_Tournament drive(all_strategies, 
							  InputParser::get_steps(),
							  matrix_from_file);
		drive.play();
	}
	
	for (Strategy *st : all_strategies)
	{
		delete st;
	}
}
 

int main(int argc, char **argv)
{
	GetParameters(argc,argv);
	Matrix_T matrix_from_file = ReadMatrix(InputParser::get_matrix());
	PlayGame(matrix_from_file);
	return 0;
}