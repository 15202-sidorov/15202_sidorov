#include "GameRun.h"

void PlayGame(int argc, char **argv)
{
	InputParser GameInfo(argc,argv);

	std::string mode_name = GameInfo.mode_name;
	int steps = GameInfo.steps;
	std::vector<std::string> strategy_name 
		= GameInfo.strategy_name;

	MatrixReader Matrix( GameInfo.matrix_file_name );

	// auto
	auto f = Factory<Strategy,
					 std::string,
					 std::function<Strategy *()>> :: getInstance();

	// unique_ptr
	std::vector<std::unique_ptr<Strategy>> all_strategies;
	for( std::string name : strategy_name )
	{
		std::unique_ptr<Strategy> ptr(f -> create(name));
		all_strategies.push_back(std::move(ptr));
	}
	
	std::cout << "Ready to play " << mode_name << std::endl;


	std::unique_ptr<Game> g;
	
	if ( mode_name == "detailed" )
	{
		g.reset(new Game_Detailed(std::move(all_strategies),
									steps,
									Matrix.MatrixInFile));
	}
 	
	else if ( mode_name == "fast" )
	{
		g.reset(new Game_Not_Detailed(std::move(all_strategies),
						  		 	  steps,
						  		      Matrix.MatrixInFile));
	}
	else if ( mode_name == "tournament" )
	{
		g.reset(new Game_Tournament(std::move(all_strategies), 
							        steps,
							        Matrix.MatrixInFile));
	}
	
	g->play();
	
}