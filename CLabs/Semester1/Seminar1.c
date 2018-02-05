#include <stdio.h>

int fact(int x)
{
	if (x > 1) return x*fact(x-1);
	else return 1;

}

int fib(int n)
{
	int a;
	if ((n == 1)||(n == 2))
		
		return 1;
	
	else return fib(n-1)+fib(n-2);
		
}

int max_elem(int v[3], int n)
{
	int i;
	int max = v[0];
	for (i = 0; i < n; i++)
		if (v[i] > max) max = v[i];
	return max;	

}


int main()
{
	
	int i;
	int m[3];
	printf("%d\n",fact(4));
	
	printf("---\n");
	for (i = 1; i < 10; i++) printf("%d\n",fib(i));
	
	printf("----\n");
	m[1] = 3;
	m[3] = 5;
	m[2] = 6;
	m[0] = 4;
	printf("%d\n",max_elem(m,3));


}

