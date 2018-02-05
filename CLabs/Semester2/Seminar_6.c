#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//DPLL
//проверки
//ll применять каждый раз
// example : (x y z) (x !x) (!z)
//(x y) (!y z !d) (d  !k)
#define VAR_NUM 5 + 1
#define C_NUM 3

typedef 
	enum 
	{
		F = -1,
		NOTHING,
		T
	}state;

//checks out whether the formula is right in current interpritation states
int check_interpritation(int formulae[C_NUM][VAR_NUM], state variables[VAR_NUM])
{
	int i = 0;
	int j = 0;
	//checking out all dises
	for (i = 0; i < C_NUM; i++)
	{
		int true_dis = 0;
		//checking out all variables
		for (j = 0; j < VAR_NUM - 1; j++)
		{
			// if at least one of them is true, moveing forward
			if (formulae[i][j] * variables[abs(formulae[i][j])] > 0) 
			{
				true_dis = 1;
				continue;
			}		
		}
		if (!true_dis)
		{
			return 0;
		}
		
	}
	return 1;
}

//returns how many variables were interpritated
int LL_optimization(int formulae[C_NUM][VAR_NUM],state variables[VAR_NUM])
{
	//finding lonely variable in a disjuntion
	int counter_var_LL1 = 0;
	for (int i = 0; i < C_NUM; i++)
	{
		int counter = 0;
		int potential = 0;
		for (int j = 0; j < VAR_NUM - 1; j++)
		{
			if (formulae[i][j] == 0)
			{
				counter++;
			}
			else
			{
				potential = formulae[i][j];
			}
		}
		
		if ((counter == VAR_NUM - 2) && (variables[abs(potential)] == NOTHING))
		{
			variables[abs(potential)] = (potential > 0) ? T : F;
			counter_var_LL1++;
			printf("varibale id : %d is lonely\n",abs(potential));
		}
	}
	
	//finding "good" variables
	int counter_var_LL2 = 0;
	int flags[VAR_NUM] = {0};
	for (int i = 0; i < C_NUM; i++)
	{
		for (int j = 0; j < VAR_NUM; j++)
		{
			if ((formulae[i][j] == 0) || (flags[abs(formulae[i][j])] == -2))
			{
				continue;
			}
			if (variables[abs(formulae[i][j])] != NOTHING)
			{
				if (flags[abs(formulae[i][j])] != -2) 
				{
					counter_var_LL2--;
				}
				continue;
			}
			if (flags[abs(formulae[i][j])] * formulae[i][j] < 0)
			{	
				flags[abs(formulae[i][j])] = -2;
				variables[abs(formulae[i][j])] = NOTHING;
				counter_var_LL2--;
			}
			else
			{
				flags[abs(formulae[i][j])] = (formulae[i][j] > 0) ? T : F;
				variables[abs(formulae[i][j])] = (formulae[i][j] > 0) ? T : F;
			}
		
		}
	}

	return counter_var_LL1 + VAR_NUM - 1 - counter_var_LL1;
}

//prints the solution
int find_solution(int formulae[C_NUM][VAR_NUM], state variables[VAR_NUM], int counter, int sum_of_LL)
{
	//means all the variables are interpritated
	if (sum_of_LL + counter >= VAR_NUM - 1)
	{
		if (check_interpritation(formulae,variables))
		{
			return 1;
		}
		return 0;
	}
	counter++;
	
	sum_of_LL += LL_optimization(formulae,variables);
	if (sum_of_LL + counter >= VAR_NUM - 1)
	{
		return 1;
	}

	if (variables[counter] != NOTHING) // if variable is in LL_optimization
	{
		if (find_solution(formulae,variables,counter,sum_of_LL))
		{
			return 1;
		}
		return 0;
	}

	variables[counter] = T;
	if (find_solution(formulae,variables,counter,sum_of_LL))
	{
		return 1;
	}
	variables[counter] = F;
	if (find_solution(formulae,variables,counter,sum_of_LL))
	{	
		return 1;
	}
	variables[counter] = NOTHING;

	return 0;
}

int main()
{
	//current values of all variables
	//current state of variables (from 1.. to N)
	state variables[VAR_NUM] = {0};

	//- - means inversion
	int formulae[C_NUM][VAR_NUM] = {
		{1,2,0,0,0},{0,-2,3,-4,0},{0,0,0,4,-5}
	};

	if (find_solution(formulae,variables,0,0))
	{
		printf("all done\n");
		for (int i = 1; i < VAR_NUM; i++)
		{
			printf("id : %d is : %d\n",i,variables[i]);
		}
	}
	else
	{
		printf("nothing is found\n");
	}

	return 0;
}