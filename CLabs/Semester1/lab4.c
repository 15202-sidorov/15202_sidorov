#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MULT 2
#define START_LENGTH 10

typedef struct Inf_s
{
	int length;
	int count;
	char *s;

} inf_s;

void init (inf_s *str)
{
	str->s = (char *)calloc(START_LENGTH,sizeof(char));
	str->length = START_LENGTH;
	str->count = -1;
}

void add(inf_s *str,char c) // добавлем в бесконечную строку символ
{
	assert(str);
	(str->count)++;
	int coun = str->count;

	int l = str->length;
	if (coun == l)
	{
		char *p = (char *)calloc(l*MULT,sizeof(char));
		assert(p);

		memcpy(p, str->s, (l*MULT-l)*sizeof(char));
		p[coun] = c;
		free(str->s);
		str->s = p;
		(str->length) *= MULT;
	}
	else
	{
		str->s[coun] = c;
	}		
	return;
}

void get_inf_s(inf_s *str)
{
	char c;
	while((c = getchar()) != '\n')
	{
		add(str,c);
		assert(str);
	}
	add(str,'\0');
	assert(str);
}

enum CHAR_TYPE
{
	ERROR = -2,
	MINUS = -1,
	PLUS,
	DIGIT,
	BIG_SIMBOL,
	SMALL_SIMBOL
};

int what_kind(char c) //определяем к какому типу принадлежит символ
{
	if ((c >= '0') && (c <= '9')) return DIGIT;
	if ((c >= 'A') && (c <= 'Z')) return BIG_SIMBOL;
	if ((c >= 'a') && (c <= 'z')) return SMALL_SIMBOL;
	if ('-' == c) return MINUS;
	if ('+' == c) return PLUS;
	return ERROR;
}

int check_simbol(int c, int from)
{
	return (c < from);
}

int *read_the_digit(inf_s str, int from,int *length)// считываем число  в arr и проверяем его
{
	
	int *arr = (int *)calloc(str.count+1,sizeof(int));
	
	int has_sign = 0;
	switch(what_kind(str.s[0]))
	{
		case ERROR:
			free(arr);
			return NULL;
			break;
		case MINUS:
			arr[0] = MINUS;
			has_sign = 1;
			break;
		case PLUS:
			arr[0] = PLUS;
			has_sign = 1;
			break;
		default:
			arr[0] = PLUS;
			break;
	}
	
	int no_sign = !has_sign;

	int i;
	for (i = has_sign; i < str.count; i++)
	{
		
		switch(what_kind(str.s[i]))
		{
			case ERROR: case MINUS: case PLUS:
				free(arr);
				return NULL;
				break;
			case BIG_SIMBOL:
				arr[i+no_sign] = (int)(str.s[i] - 'A' + 10);
				break;
			case SMALL_SIMBOL:
				arr[i+no_sign] = (int)(str.s[i] - 'a' + 10);
				break;
			case DIGIT:
				arr[i+no_sign] = (int)(str.s[i] - '0');
				break;
		}
		
		if (0 == check_simbol(arr[i+1],from))
		{
			free(arr);
			return NULL;
			break;
		}
	}

	*length = str.count + no_sign;

	return arr;
}


int to_10(const int *digit, int from, int length)
{
	int i;
	int sum = 0;
	int deg = 1;
	for (i = length-1; 0 < i; i--)
	{
		sum += digit[i]*deg; 
		deg *= from;
	}
	
	return sum;
}

void swap(int *x, int *y)
{
	int r = *x;
	*x = *y;
	*y = r;
}

void intrev(int *s,int length) 
{
	int i = 0, j = 0;
	
	for (i = length-1; (length-1)/2 < i; i--)
	{
		swap((s + j),(s + i));
		j++;
	}
}

int *from_10(int d, int to, int *length)
{
	
	int i = 0;    // ???
	int *d1 = NULL;
	int *d2 = NULL;   // ???

	if (d < 0) d *= -1;
	*length = 1;
	d2 = (int *)calloc(2,sizeof(int));
	d2[0] = d % to;
	d /= to;
	for (i = 1; d > 0; i++)
	{
		d1 = (int *)calloc(i+1,sizeof(int));
		memcpy(d1,d2,i*sizeof(int));
		free(d2);
		d1[i] = d % to;
		d /= to;
		d2 = d1;
		
		(*length)++;
	}
	(*length)++;
	d1 = (int *)calloc((*length)+1,sizeof(int));
	memcpy(d1,d2,(*length)*sizeof(int));
	free(d2);
	d1[i] = d % to;
	d /= to;
	d2 = d1;
	intrev(d1,*length);
	return d1;
}

void translate(inf_s *str,const int *arr, int length)
{
	int i;
	
	if (MINUS == arr[0])
	{
		add(str,'-');
	}
	
	for (i = 1; i < length; i++)
	{
		if (arr[i] <= 9)
		{
			add(str,(char)(arr[i] + '0'));
		}
		else 
		{
			add(str,(char)(arr[i] + 'A' - 10));
		}
	}
	add(str,'\0');
	
	return;
}



int main(int argc, char **argv)
{
	int *arr_from = NULL,*arr_to = NULL;
	int from = 0;
	
	scanf("%d",&from);
	getchar();
	
	inf_s s1,s2;

	init(&s1);
	get_inf_s(&s1);
	if (NULL == &s1) //?? как все ошибки обрабатывать более эффективней?
	{
		fprintf(stderr,"NOT ENOUGH MEMORY");
		return 0;
	}
	
	int length = 0;
	arr_from = read_the_digit(s1,from,&length);
	if (NULL == arr_from)
	{
		fprintf(stderr,"THE SYSTEM DOES NOT FIT",argv[0]);
		free(arr_from);
		free(s1.s);
		
		return 0;
	}
	

	int ten = to_10(arr_from,from,length);
	if (ten < 0)
	{
		free(arr_from);
		free(s1.s);
		printf("%d\n",ten);
		fprintf(stderr,"The digit is too long,bro",argv[0]);
		return 0;
	}

	int to;
	scanf("%d",&to);
	getchar();	
	if (0 == to) 
	{
		free(arr_from);
		free(s1.s);
		fprintf(stderr,"THERE IS NO SUCH SYSTEM",argv[0]);
		return 0;
	}
	arr_to = from_10(ten,to,&length);
	arr_to[0] = arr_from[0];
	
	init(&s2);
	translate(&s2,arr_to,length);

	printf("The digit %s in system %d is translated to %d as ",s1.s,from,to);
	if ('-' == s1.s[0])
	{
		printf("%c",'-');
		
	}
	printf("%s\n",s2.s);
	

	free(arr_from);
	free(s1.s);
	free(s2.s);
	free(arr_to);

	return 0;
}