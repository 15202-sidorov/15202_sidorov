#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 64
#define MANT 52
#define EXP 11

char *get_bits(unsigned long long int d)
{
    if (0 > d)
    {
        d *= -1;
    }
    char *s = (char *)calloc(SIZE,sizeof(char));
    int i = SIZE - 1;
    while (0 != d)
    {
        s[i] = d % 2;
        d /= 2;
        i--;
    }
    return s;
}

void array_out(const char *s,int length)
{
    int i;
    for (i = SIZE - length; i < SIZE; i++)
    {
        printf("%d",(int)s[i]);
    }

}

unsigned long long int get_SIGN(unsigned long long d)
{
    d >>= SIZE - 1;
    return d;
}

unsigned long long int get_E(unsigned long long int d)
{

    d <<= 1;
    d >>= MANT+1;
    return d;
}

unsigned long long int get_M(unsigned long long int d)
{

    d <<= EXP+1;
    d >>= EXP+1;
    return d;
}

double frac_trans(char *s) //искомая мантисса
{
    int i;
    double sum = 0;
    double deg = 0.5;


    for (i = SIZE - MANT; i < SIZE; i++)
    {
        sum += (int)(s[i])*deg;
        
        deg /= 2;
    }

    return sum+1;
}

int main(int argc, char **argv)
{
    int flag = 0;
    while (1)
    {
        double x;
        
        int rc = scanf("%lf",&x);
        if (1 != rc)
        {
           
            if (!flag) 
            {
                 fprintf(stderr,"You entered a wrong charackter\n",argv[0]);
                flag++;
            }
            getchar();
            continue;
        }
        getchar();
        flag = 0;
        if (0 == x)
        {
            printf("%d\n",0);
            return 0;
        }

        unsigned long long int d = 0,d1 = 0;
        memcpy(&d,&x,sizeof(long long int));



        unsigned long long int sign = get_SIGN(d),
                        frac = get_M(d),
                        e = get_E(d);
        printf("%s\n","The digit itself:");
        printf("%lld\n",d);
        char *s = get_bits(d);
        array_out(s,SIZE);
        printf("\n\n");


        e = e - 1023;

        d1 = get_SIGN(d);
        char c;
        if (1 == d1)
        {
            c = '-';
        }
        else
        {
            c = '+';
        }
        printf("%c",c);

        printf("%s","1.");
        s = get_bits(frac);

        array_out(s,MANT);
        printf("%s","*2^");
        s = get_bits(e);
        array_out(s,EXP);
        printf("\n\n");

        s = get_bits(frac);
        double d_dbl = frac_trans(s);
        printf("%f*2^%d\n",d_dbl,e);

        free(s);


    }
    
    return 0;
}