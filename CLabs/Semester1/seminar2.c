#include <stdio.h>


int main()
{
	int *p;
	int i;

	p = &i;
	printf("%x\n",p);
	
	*p = 1;
	printf("%d\n",*p);
	
	int a[] = {6, 0, 3, 1, 7, 6, 9}; 
	p = a;
	printf("%d\n",*(p+4));

	printf("%d\n",sizeof(a));
	printf("%d\n",sizeof(p));
	

	return 0;
}