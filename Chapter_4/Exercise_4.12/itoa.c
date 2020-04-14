#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 100

/*
 * Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 */

void itoa(int n, char s[]);

int main(void)
{
    int n = 575;
    char s[MAX_LENGTH];
    itoa(n, s);
    printf("Number: %s\n", s);
    return 0;
}

void itoa(int n, char s[])
{
    static int i;
    if (n / 10)
    {
        itoa(n / 10, s);
    }
    else
    {
        i = 0;
        if (n < 0)
            s[i++] = '-';
    }
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}
