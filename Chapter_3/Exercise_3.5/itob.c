#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

/*
 * Write the function itob(n,s,b) that converts the integer n into a base b character representation
 * in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
 */

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void)
{
    int number = 101;
    int base = 16;
    char str[MAX_LENGTH];

    itob(number, str, base);

    printf("Result for %d with base %d = %s\n", number, base, str);
    return 0;
}

void itob(int n, char s[], int b)
{
    int i = 0;
    int j;
    int sign;

    if ((sign = n) < 0)
        n = -n;
    
    do
    {
        j = n % b;
        s[i++] = (j <= 9) ? j + '0' : j + 'a' - 10;
    } while ((n /= b) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
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
