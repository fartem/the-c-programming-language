#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define SIZE 100

/*
 * Write getfloat, the floating-point analog of getint.
 * What type does getfloat return as its function value?
 */

int getch(void);
void ungetch(int);

int getfloat(float *);

int main(void)
{
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        printf("%f\n", array[n]);

    return 0;
}

int getfloat(float *pn)
{
    int c, sign;
    float power;

    while (isspace(c = getch()))
        ;
    
    while (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    if (c == '.')
        c = getch();
    
    for (power = 1.0; isdigit(c); c = getch())
    {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }

    *pn *= sign / power;

    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFER_SIZE)
        printf("ungetch: Error! Too many character in buffer!");
    else
        buffer[bufp++] = c;
}
