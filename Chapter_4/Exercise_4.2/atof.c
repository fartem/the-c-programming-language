#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 1000

double atof(char s[]);
int power(int base, int exp);
int getLine(char s[], int limit);

int main()
{
    char s[MAX_LENGTH];
    double num;

    getLine(s, MAX_LENGTH);

    num = atof(s);

    printf("Result: %f\n", num);
    return 0;
}

double atof(char s[])
{
    double val;
    double pow;

    int sign;
    int i;
    int esign;
    int exp;

    for (i = 0; isspace(s[i]); i++)
        ;
    
    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    
    for (val = 0.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
    }
    
    if (s[i] == '.')
    {
        i++;
    }
    
    for (pow = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        pow *= 10.0;
    }
    
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
    }
    
    if (s[i] == '+' || s[i] == '-')
    {
        esign = s[i];
        i++;
    }

    for (exp = 0; isdigit(s[i]); i++)
    {
        exp = 10.0 * exp + (s[i] - '0');
    }
    
    if (esign == '-')
    {
        return sign * (val / pow) / power(10, exp);
    }
    else
    {
       return sign * (val / pow) * power(10, exp);
    }
}

int power(int base, int exp)
{
    int power = 1;
    while (exp-- > 0)
    {
        power *= base;
    }
    return power;
}

int getLine(char s[], int limit)
{
    int c;
    int i;
    
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
}
