#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define alive '#'
#define dead '-'

struct game
{
	int nt; // the width and length of a feild
	int mt;
	char **feild; //the feild itself
	int *b; // the rules of game
	int *s;
};

char **get_mem(int n, int m) 
{	
	int i;
	char **arr;
	arr = (char **)calloc(n,sizeof(char *)); 
	for (i = 0; i < n; i++)
	{
		arr[i] = (char *)calloc(m,sizeof(char));
	} 
	return arr;

}

void free_mem(char **arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

int count_living(int x, int y,char **arr,int nmax, int mmax) 
{	
	int i = 0, j = 0,sum = 0,k = 0 ,l = 0;
	for (i = x - 1; i <= x + 1; i++)
		for (j = y - 1; j <= y + 1; j++)
		{
			k = i;
			l = j;
			if ((i == x) && (j == y)) continue;
			if (-1 == i) 
			{
				k = nmax-1;
			}
			if (-1 == j) 
			{
				l = mmax-1;
			}
			if (nmax == i)
			{
				k = 0;
			} 
			if (mmax == j) 
			{
				l = 0;
			}
			if (alive == arr[k][l])
			{
				sum ++;
			}
				
		}
	return sum;
}

char **next_step(char **arr, int b_arr[9], int s_arr[9], int n, int m) 
{
	
	int i = 0, j = 0,count = 0;
	char **arr2;
	arr2 = get_mem(n,m);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			count = count_living(i,j,arr,n,m);
			switch (arr[i][j])
			{
				case alive:
					arr2[i][j] = dead;
					int k = 0;
					for (k = 1; k < 9; k++)
					{
						
						if ((count == k) && (1 == s_arr[k]))
						{
							arr2[i][j] = alive;
						}
					}
				 	break;
				case dead:
					arr2[i][j] = dead;
					for (k = 1; k < 9; k++)
					{
						if ((count == k) && (1 == b_arr[k]))
						{
							arr2[i][j] = alive;
							break;
						}
					}
				 	break;
			}

		}
	return arr2;
}

void array_out(char **arr, int n, int m) 
{
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				printf("%c",arr[i][j]);
				
			}
			printf("%c\n",' ');
		}
}

void read_from_file(struct game *fvalue,char *argv)
{
	struct game fv;
	int n,m;
	int i = 0, j = 0;
	char **arr;
	
	FILE* input_file = fopen(argv,"r");
	if (NULL == input_file)
	{
		printf("No input file");
		return;
	}
	
	int rc = fscanf(input_file,"#Size height %d width %d #R B",&n,&m);
	
	if (2 != rc)
	{
		fprintf(stderr,"Enter width and height",argv);
		fclose(input_file);
		return;
	}
	
	//defining the conditions of burth or surviving
	char let;
	int *b_arr = (int *)calloc(9,sizeof(int)); 
	int *s_arr = (int *)calloc(9,sizeof(int));
	while((let = fgetc(input_file)) != '/')
	{
		i = atoi(&let);
		if (i > 8) 
		{
			fprintf(stderr,"Burth value is more thаn 8",argv);
			fclose(input_file);
			return;
		}
		if (0 == b_arr[i])
		{
			b_arr[i] = 1;
		}
	}
	fscanf(input_file,"S");

	while((let = fgetc(input_file)) != '\n')
	{
		
		i = atoi(&let);
		;
		if (i > 8) 
		{
			fprintf(stderr,"Survive value is more then 8",argv);
			fclose(input_file);
			return;
		}
		if (0 == s_arr[i])
		{
			s_arr[i] = 1;
		}
	}
	

	for (i = 1; i < 9; i++)
	{
		if(b_arr[i] != 1) b_arr[i] = -1;
		if(s_arr[i] != 1) s_arr[i] = -1;
		
	}	

	
	arr = get_mem(n,m);
	
	if (NULL == arr) 
	{
		printf("No memory");
		return;
	}
	
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			arr[i][j] = dead;
		}
	
	
	while(1) // reading the coordinats of alive cells
	{
		int k,l;
		int rc = fscanf(input_file,"%d %d\n",&k,&l);
		if (2 == rc) arr[k][l] = alive;
		else break;
	}
	
	fv.nt = n;
	printf("%d\n",n);
	fv.mt = m;
	fv.feild = arr;
	fv.b = b_arr;
	fv.s = s_arr;

	*fvalue = fv;
	printf("%d\n",n);
	fclose(input_file);
	return;
}

int main(int argc, char **argv)
{
	
	char **arr = NULL;
	char **arr2 = NULL;
	struct game all_data;
	
	read_from_file(&all_data,argv[1]);
	if (NULL == &all_data)
	{
		return 0;
	}
	arr = all_data.feild;

	array_out(arr,all_data.nt,all_data.mt);
	
	
	while(getchar() != 'E')
	{
		arr2 = next_step(arr,all_data.b,all_data.s,all_data.nt,all_data.mt);
		array_out(arr2,all_data.nt,all_data.mt);
		arr = arr2;
	}
	free(all_data.b);
	free(all_data.s);	
	free_mem(arr,all_data.nt);
	free_mem(arr2,all_data.nt);
	
	return 0;
}