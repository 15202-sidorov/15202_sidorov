#include "GameRun.h"

int main(int argc, char **argv)
{
	try
	{
		PlayGame(argc,argv);
	}
	catch(std::exception)
	{
		std::cerr << "Strategy is not found" << std::endl;
	}
	catch(ERROR_ID err)
	{
		switch(err)
		{	
			case STRATEGY_ERROR:
				std::cerr << "Not enough strategies" << std::endl;
				break;
			case STEPS_ERROR:
				std::cerr << "Incorrect steps" << std::endl;
				break;
			case MODE_ERROR:
				std::cerr << "Incorrect mode" << std::endl;
				break;		
		}
	}
	return 0;
}