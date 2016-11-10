#include <iostream>
#include <fstream>
#include <exception>

int main()
{
	std::ifstream file_stream;
	file_stream.open("text_file.txt");
	if(!file_stream.is_open())
	{
		throw -1;
	}


	int space1,space2;

	file_stream >> space1 >> space2;
	std::cout << space1 <space2 << std::endl;
	file_stream.close();

	return 0;
}