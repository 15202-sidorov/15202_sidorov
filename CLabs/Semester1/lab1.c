#include <stdio.h>
#include <stdlib.h>

#define DIGIT 2000000

void resheto(int *a)
{
	long long int i = 0;
	long long int j = 0;
	
	for (i = 2; i <= DIGIT; i++)
	{
		if (a[i] == 0)
		{
			for(j = 2; i*j <= DIGIT; j++)
				a[i*j] = 1;
		}
			
	}
	
	
}

long long int sum(int *a) // returns the final sum
{
	long long int s = 0, i = 0;
	
	for (i = 2; DIGIT >= i; i++)
		if (0 == a[i]){
			s += i;
		} 
			
	return s;

} 

int main()
{
	int *all = (int *)calloc(DIGIT,sizeof(int));
	if (NULL != all) 
	{
		resheto(all);
		printf("%lld\n",sum(all));
		free(all);
		return 0;
	}
	else 
		printf("NO MEMORY");
}
