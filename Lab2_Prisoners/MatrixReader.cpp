#include "MatrixReader.h"

MatrixReader::MatrixReader( std::string matrix_file_name )
{
	std::ifstream file;
	
	if (matrix_file_name == "default")
	{
		//setting default matrix
		MatrixInFile = 
			{
			//m1  - Cooperate
				{
				//m2 - Cooperate
				{
					//m3 - Cooperate
					{
						//all cooperate
						{1 , 1, 1}
					},
					//m3 - Deny
					{
		  				//1 1 0
						{3, 3, 0}
					}
				},
				//m2 - Deny
				{
					{
						//1 0 1
						{3, 0, 3}
					},
					{
						//1 0 0
						{5, 2, 2}
					}
				}
			},
			//m1 - Deny
			{
				{
					{
						//0 1 1
						{0, 3, 3}
					},
					{
						//0 1 0
						{2, 5, 2}
					}
				},
				{
					{
						//0 0 1
						{2, 2, 5}
					},
					{	
						//0 0 0
						{4, 4, 4}
					}
				}
			}
		};
		return;
	}
	file.exceptions(std::ifstream::failbit);
	file.open(matrix_file_name);


	//setting NULL matrix
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
		if (file.eof())
		{
			throw -1;
		}
		MatrixInFile[i1][i2][i3] = tmp;
	}
	return; 
}
