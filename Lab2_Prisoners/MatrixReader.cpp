#include "MatrixReader.h"

Matrix_T MatrixReader::MatrixInFile;

void MatrixReader::Read()
{
	std::ifstream file;
	file.open(InputParser::matrix_file_name);
	if (!file.is_open())
	{
		std::cout << "Can't find file" << std::endl;
		exit(-1);
	}

	MatrixInFile.push_back({
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
	MatrixInFile.push_back({
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
		try
		{
			if (file.eof())
			{
				throw -1;
			}
		}
		catch(int)
		{
			std::cerr << "Not enough matrix" << std::endl;
			exit(-1);
		}
		MatrixInFile[i1][i2][i3] = tmp;
	}

	file.close();
	return; 
}
