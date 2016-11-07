#include "GameRun.h"

void PlayGame()
{
	Factory<Strategy,std::string,std::function<Strategy *()>> *f =
	Factory<Strategy,std::string,std::function<Strategy *()>> :: getInstance();

	std::vector<Strategy *> all_strategies;
	for(std::string name : InputParser::strategy_name)
	{
		all_strategies.push_back(f -> create(name));
	}
	
	if (InputParser::mode_name == "detailed")
	{
		Game_Detailed drive(all_strategies,
						    InputParser::steps,
						    MatrixReader::MatrixInFile);
		drive.play();
	}
	else if (InputParser::mode_name == "fast")
	{
		Game_Not_Detailed drive(all_strategies,
						  		InputParser::steps,
						  		MatrixReader::MatrixInFile);
		drive.play();
	}
	else if (InputParser::mode_name == "tournament")
	{
		Game_Tournament drive(all_strategies, 
							  InputParser::steps,
							  MatrixReader::MatrixInFile);
		drive.play();
	}
	
	for (Strategy *st : all_strategies)
	{
		delete st;
	}
}