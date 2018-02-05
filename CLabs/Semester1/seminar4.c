#include <stdio.h>
#include <stdlib.h>

//https://github.com/iefremov/tundra-x/blob/master/tundra/website/1st-strings.md

void swap(char *x, char *y)
{
	char r;
	r = *x;
	*x = *y;
	*y = r;
}

int strlen(char *s)
{
	int i = 0, sum = 0;
	for (i = 0; '\0' != s[i]; i++)
		sum++;

	return sum;

}

void strrev(char *s) 
{
	
	int i,j;
	

	j = 0;
	for (i = strlen(s)-1; ((strlen(s)-1)/2) < i; i--)
	{
		
		swap((s + j),(s + i));
		j++;
	}
}

void inttoa(int n, char *s)
{
	
	int j = 0;
	int k ;
	while (n > 0)
	{
		k = n % 10; // check out the last digit
		*(s + j) = (k + 48); // add it to the string
		j++;
		n = (n - (n % 10))/10; // reduce n
		
	}
	

}

int main()
{
	char *s;
	int k,n,sum = 0;
	
	scanf("%d",&n);
	
	k = n;
	while (k > 0)
	{
		k = (k - (k % 10))/10;
		sum++;
	}

	s = (char *)calloc(sum+1,sizeof(char));
	s[sum+1] = '\0';

	inttoa(n,s);
	strrev(s);
	printf("%s\n",s);
	free(s);



}