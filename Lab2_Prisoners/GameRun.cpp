#include "GameRun.h"

void PlayGame()
{
	// auto
	auto f = Factory<Strategy,
					 std::string,
					 std::function<Strategy *()>> 
					 :: getInstance();

	// unique_ptr
	std::vector<std::unique_ptr<Strategy>> all_strategies;
	for(std::string name : InputParser::strategy_name)
	{
		std::unique_ptr<Strategy> ptr(f -> create(name));
		all_strategies.push_back(std::move(ptr));
	}
	
	std::cout << "Ready to play " << InputParser::mode_name << std::endl;

	Game * g = nullptr;
	if (InputParser::mode_name == "detailed")
	{
		static Game_Detailed drive(std::move(all_strategies),
						    InputParser::steps,
						    MatrixReader::MatrixInFile);
		g = &drive;
	}
	else if (InputParser::mode_name == "fast")
	{
		static Game_Not_Detailed drive(std::move(all_strategies),
						  		InputParser::steps,
						  		MatrixReader::MatrixInFile);
		g = &drive;
	}
	else if (InputParser::mode_name == "tournament")
	{
		static Game_Tournament drive(std::move(all_strategies), 
							  InputParser::steps,
							  MatrixReader::MatrixInFile);
		g = &drive;
	}

	g->play();
}