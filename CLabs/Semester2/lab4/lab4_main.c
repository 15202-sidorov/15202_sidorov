#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "inf_s.h"
#include "list.h"

/*
	DNA alignment.
	DNAfull scoring matrix and corresponding gap penalties are used.
*/
#define GAP_OPEN -10
#define GAP_EXTEND -1
#define MATCH 5
#define MISMATCH -4


//defines whether i,j sequences are ending with
typedef
	enum END_GAP_STATE
	{
		ENDS_WITH_GAP,
		DOES_NOT_END_WITH_GAP,
		BOTH_POSSIBLE
	}end_gap_state;

typedef
	struct ALIGNMENT_STATE
	{
		end_gap_state state_1;
		end_gap_state state_2;
		int score;
	}alignment_state;



//checking whether all symbols are in the alphabet
int check_alphabet(inf_s string)
{
	int i = 0;
	for (i = 0; i < string.count; i++)
	{
		switch (string.s[i])
		{
			case 'G' : 
				continue;
				break;
			case 'A' :
				continue;
				break;
			case 'C' :
				continue;
				break;
			case 'T' :
				continue;
				break;
			default :
				printf("%c\n",string.s[i]);
				return 0;
		}

	}
	return 1;
}

//allocating the matrix
alignment_state **matr_calloc(int size_1, int size_2)
{
	int i = 0;
	alignment_state **result = (alignment_state **)calloc(size_1,sizeof(alignment_state *));
	for (i = 0; i < size_1; i++)
	{
		result[i] = (alignment_state *)calloc(size_2,sizeof(alignment_state));
	}
	
	return result;
}

void free_matr(alignment_state **matr, int size_1, int size_2)
{
	int i = 0;
	for (i = 0; i < size_1; i++)
	{
		free(matr[i]);
	}
	free(matr);
	return ;
}

int max(int x, int y, int z)
{
	if ((x >= y) && (x >= z))
	{
		return x;
	}
	else if ((y >= z) && (y >= x))
	{
		return y;
	}
	else 
	{
		return z;
	}
}

int match(char a, char b)
{
	if (a == b)
	{
		return MATCH;
	}
	return MISMATCH;
}

void printf_scores(FILE *output_file,alignment_state **matr,int n, int m)
{
	int i = 0; 
	int j = 0;
	fprintf(output_file,"The matrix of calculation is : \n");

	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			fprintf(output_file,"%3d ",matr[i][j].score);
		}
		fprintf(output_file,"\n");
	}

	return;
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void reverse(char *string)
{
	int i = 0;
	int j = 0;
	while (string[j] != '\0')
	{
		j++;
	}
	j--;
	while (i < j)
	{
		swap(string+i, string+j);
		j--;
		i++;
	}
	return;
	
}

void printf_result(FILE *output_file,alignment_state **matr,int i, int j,inf_s code_1, inf_s code_2)
{
	inf_s alignment_1; init_s(&alignment_1);
	inf_s alignment_2; init_s(&alignment_2);
	while ((i > 0) && (j > 0))
	{
		if ((matr[i][j].score == matr[i-1][j-1].score + match(code_1.s[i-1],code_2.s[j-1]))
			&& (matr[i][j].state_1 != ENDS_WITH_GAP) && (matr[i][j].state_2 != ENDS_WITH_GAP))
		{
			add(&alignment_1,code_1.s[i-1]);
			add(&alignment_2,code_2.s[j-1]);
			i--;
			j--;
		}
		else if ((matr[i][j].score == matr[i-1][j].score + GAP_OPEN) 
					|| (matr[i][j].score == matr[i-1][j].score + GAP_EXTEND))
		{
			add(&alignment_1,code_1.s[i-1]);
			add(&alignment_2,'-');
			if (matr[i][j].score == matr[i-1][j].score + GAP_EXTEND)
			{
				matr[i-1][j].state_1 = ENDS_WITH_GAP;
			}
			else
			{
				matr[i-1][j].state_1 = DOES_NOT_END_WITH_GAP;
			}
			i--;
		}
		else if ((matr[i][j].score == matr[i][j-1].score + GAP_OPEN) 
				|| (matr[i][j].score == matr[i][j-1].score + GAP_EXTEND))
		{
			add(&alignment_1,'-');
			add(&alignment_2,code_2.s[j-1]);
			if (matr[i][j].score == matr[i][j-1].score + GAP_EXTEND)
			{
				matr[i][j-1].state_1 = ENDS_WITH_GAP;
			}
			else
			{
				matr[i][j-1].state_1 = DOES_NOT_END_WITH_GAP;
			}
			j--;
		}
	}

	while (i > 0)
	{
		add(&alignment_2,'-');
		add(&alignment_1,code_1.s[i-1]);
		i--;
	}
	while (j > 0)
	{
		add(&alignment_1,'-');
		add(&alignment_2,code_2.s[j-1]);
		j--;
	}
	add(&alignment_1,'\0');
	add(&alignment_2,'\0');
	reverse(alignment_1.s);
	reverse(alignment_2.s);
	fprintf(output_file,"The resulted alignment is : \n");
	fprintf(output_file,"%s\n",alignment_1.s);
	fprintf(output_file,"\n");
	fprintf(output_file,"%s\n",alignment_2.s);
	free(alignment_1.s);
	free(alignment_2.s);
	
}

void matr_init(alignment_state **matr, int size_1, int size_2)
{
	int i = 0;
	int j = 0;
	matr[0][0].score = 0;
	matr[0][0].state_1 = DOES_NOT_END_WITH_GAP;
	matr[0][0].state_2 = DOES_NOT_END_WITH_GAP;
	matr[1][0].score = GAP_OPEN;
	matr[0][1].score = GAP_OPEN;
	matr[1][0].state_1 = ENDS_WITH_GAP;
	matr[1][0].state_2 = DOES_NOT_END_WITH_GAP;
	matr[0][1].state_2 = ENDS_WITH_GAP;
	matr[0][1].state_1 = DOES_NOT_END_WITH_GAP;
	for (i = 2; i < size_1; i++)
	{
		matr[i][0].score = matr[i-1][0].score + GAP_EXTEND;
		matr[i][0].state_1 = ENDS_WITH_GAP;
		matr[i][0].state_2 = DOES_NOT_END_WITH_GAP;
	}
	for (i = 2; i < size_2; i++)
	{
		matr[0][i].score =  matr[0][i-1].score + GAP_EXTEND;
		matr[0][i].state_2 = ENDS_WITH_GAP;
		matr[0][i].state_1 = DOES_NOT_END_WITH_GAP;
	}
	return;
}

void matr_fill(alignment_state **matr, inf_s code_1, inf_s code_2, int size_1, int size_2)
{
	int i = 0;
	int j = 0;
	for (i = 1; i < size_1; i++)
	{
		for (j = 1; j < size_2; j++)
		{
			int penalty_1 = 0;
			int penalty_2 = 0;
			//по умолчанию - GAP_EXTEND
			if (matr[i-1][j].state_1 == DOES_NOT_END_WITH_GAP) 
			{
				penalty_1 = GAP_OPEN;
			}
			else 
			{
				penalty_1 = GAP_EXTEND;
			}
			
			if (matr[i][j-1].state_2 == DOES_NOT_END_WITH_GAP)
			{
				penalty_2 = GAP_OPEN;
			}
			else
			{
				penalty_2 = GAP_EXTEND;
			}
			int insert = matr[i-1][j-1].score + match(code_1.s[i-1],code_2.s[j-1]);
			int make_gap_1 = matr[i-1][j].score + penalty_1;
			int make_gap_2 = matr[i][j-1].score + penalty_2;
			matr[i][j].score = max(insert, make_gap_1, make_gap_2);
			
	
			if ((matr[i][j-1].state_2  ==  BOTH_POSSIBLE) && (matr[i-1][j].state_1 != BOTH_POSSIBLE))
			{
				if (matr[i][j].score < matr[i][j-1].score + GAP_OPEN)
				{
					make_gap_2 = matr[i][j-1].score + GAP_OPEN;
					matr[i][j].score = make_gap_2;
				}
				
			}
			else if ((matr[i][j-1].state_2  !=  BOTH_POSSIBLE) && (matr[i-1][j].state_1 == BOTH_POSSIBLE))
			{
				if (matr[i][j].score < matr[i-1][j].score + GAP_OPEN)
				{
					make_gap_1 = matr[i-1][j].score + GAP_OPEN;
					matr[i][j].score = make_gap_1;
				}
				
			}
			else if ((matr[i][j-1].state_2  ==  BOTH_POSSIBLE) && (matr[i-1][j].state_1 == BOTH_POSSIBLE))
			{
				matr[i][j].score = max(matr[i][j].score,
										matr[i-1][j].score + GAP_OPEN,
										matr[i][j-1].score + GAP_OPEN);
				if (matr[i][j].score == matr[i-1][j].score + GAP_OPEN)
				{
					make_gap_1 = matr[i-1][j].score + GAP_OPEN;
				}
				if (matr[i][j].score == matr[i][j-1].score + GAP_OPEN)
				{
					make_gap_2 = matr[i][j-1].score + GAP_OPEN;
				}
				
			}
			
			if ((insert == matr[i][j].score) && (make_gap_2 == matr[i][j].score))
			{
				matr[i][j].state_2 = BOTH_POSSIBLE;
				//printf("%d , %d\n",i,j);
			}
			else if (matr[i][j].score == make_gap_2)
			{
				matr[i][j].state_1 = DOES_NOT_END_WITH_GAP;
				matr[i][j].state_2 = ENDS_WITH_GAP;
			}
			else if (matr[i][j].score == insert)
			{
				matr[i][j].state_1 = DOES_NOT_END_WITH_GAP;
				matr[i][j].state_2 = DOES_NOT_END_WITH_GAP;
			}
			
			if ((insert == matr[i][j].score) && (make_gap_1 == matr[i][j].score))
			{
				matr[i][j].state_1 = BOTH_POSSIBLE;
				//printf("%d , %d\n",i,j);
			}
			else if (matr[i][j].score == make_gap_1)
			{
				matr[i][j].state_1 = ENDS_WITH_GAP;
				matr[i][j].state_2 = DOES_NOT_END_WITH_GAP;
			}
			else if (matr[i][j].score == insert)
			{
				matr[i][j].state_1 = DOES_NOT_END_WITH_GAP;
				matr[i][j].state_2 = DOES_NOT_END_WITH_GAP;
			}
			//printf("possible scores : %d %d %d\n",insert,make_gap_1,make_gap_2);
			
		}
	}
	return;
}

int main()
{
	inf_s code_1;
	inf_s code_2;
	FILE *input_file_1 = fopen("DNA_sequence_1.txt","r");
	FILE *input_file_2 = fopen("DNA_sequence_2.txt","r");
	FILE *output_file = fopen("alignment_file.txt","w");

	init_s(&code_1);
	init_s(&code_2);
	get_inf_s_from_file(&code_1,input_file_1);
	get_inf_s_from_file(&code_2,input_file_2);
	if (!(check_alphabet(code_1) && check_alphabet(code_2)))
	{
		fprintf(stderr,"Symbols of unknown alphabet are found\n");
		return -1;
	}
	
	int size_1 = code_1.count + 1;
	int size_2 = code_2.count + 1;
	alignment_state **matr = matr_calloc(size_1, size_2);
	 
	matr_init(matr,size_1,size_2);
	//printf_scores(output_file,matr,size_1,size_2);
	matr_fill(matr,code_1,code_2,size_1,size_2);
	printf("matr is filled\n");

	printf_scores(output_file,matr,size_1,size_2);

	fprintf(output_file,"\n");
	fprintf(output_file,"The score is %d\n",matr[size_1-1][size_2-1].score);
	fprintf(output_file,"\n");
	fprintf(output_file,"Resulted strings : \n");
	printf_result(output_file,matr,size_1 - 1,size_2 - 1,code_1,code_2);
	
	free(code_1.s);
	free(code_2.s);
	free_matr(matr,size_1,size_2);
	fclose(input_file_1);
	fclose(input_file_2);
	fclose(output_file);

	printf("Finished successfully\n");
	return 1;
}
