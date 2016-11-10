
#include "include/GameRun.h"
//STRATEGIES!
//how do we define whether to use default matrix??
//protected constructors for interfaces
//musts read
//http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
 

int main(int argc, char **argv)
{
	InputParser::Parse_Argv(argc,argv);
	MatrixReader::Read();
	PlayGame();
	return 0;
}