#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

/*
 * In a two’s complement number representation, our version of itoa does not handle
 * the largest negative number, that is, the value of n equal to -(2wordsize-1).
 * Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 */

void itoa(int n, char s[]);
void reverse(char s[]);
int abs(int x);

int main(void)
{
    int number = -2147483648;
    char str[MAX_LENGTH];

    printf("Number: %d\n", number);
    
    itoa(number, str);
    printf("Number as string: %s\n", str);
    return 0;
}

void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;

    do
    {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int abs(int x)
{
    return (x > 0) ? x : -x;
}

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
