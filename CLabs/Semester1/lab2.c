#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) 
{
	int r;
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

void char_to_int(char *s, int *n)
{
	int i,d = 1;
	*n = 0;
	for (i = strlen(s)-1; i >= 0; i--)
	{
		*n += d*((int)s[i] - 48);
		d *= 10;
	}
}


void trotter(int n)
{
	int *c = (int *)calloc(n,sizeof(int));
	int *o = (int *)calloc(n,sizeof(int));
	int *a = (int *)calloc(n,sizeof(int));
	int i,j,s,q;
	
	for (i = 1; i <= n; i++)
	{
		a[i] = i;
		o[i] = 1;
		c[i] = 0;	
	}
	
	while(1)
	{
		
		for (i = 1; i < n; i++) printf("%d",a[i]); 
		printf("%d\n",a[n]);
		j = n;
		s = 0;

		while (1)
		{
			q = c[j] + o[j];
			
			if (q == j) 
			{
				if (1 == j) return;
				else s++;
				o[j] = -o[j];
				j--;
				continue;
			}
			else if (0 > q)
			{
				o[j] = -o[j];
				j--;
				continue;
			}
			swap(&a[j-c[j]+s],&a[j-q+s]);
			c[j] = q;
			break;
		}
		
	}
	free(o);
	free(c);
	free(a);

}

int main(int argc, char **argv)
{
	int n;
	
	if (NULL == argv[1])
	{
		scanf("%d",&n);
	}
	else
	{
		char_to_int(argv[1],&n);
	}
	trotter(n);

	return;

}