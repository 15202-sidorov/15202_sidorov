#include "GameRun.h"

int main(int argc, char **argv)
{
	InputParser::Parse_Argv(argc,argv);
	MatrixReader::Read();
	PlayGame();
	return 0;
}