#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000

/*
 * Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough.
 */

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main(void)
{
    int number = 509;
    int width = 10;
    char str[MAX_LENGTH];

    itoa(number, str, width);

    printf("%s\n", str);
    return 0;
}

void itoa(int n, char s[], int w)
{
    int i = 0;
    int sign;

    if ((sign = n) < 0)
        n = -n;
    
    do
    {
        s[i++] = (n % 10) + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';

    while (i < w)
        s[i++] = ' ';

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
