#ifndef GAME_H
#define GAME_H

#include "Strategy.h"
#include <iostream>
#include <vector>

using Matrix_T = std::vector<std :: vector<std :: vector<std :: vector<int>>>>;

class Game
{
public:
	virtual void play() = 0;
	virtual ~Game(){};
protected:
	Game(){};
	Matrix_T matrix = 
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
	std::vector<int> count_result(move m1, move m2, move m3){ return matrix[m1][m2][m3]; };

};




#endif