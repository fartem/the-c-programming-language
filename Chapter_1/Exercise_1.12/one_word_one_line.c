#include <stdio.h>

/*
 * Write a program that prints its input one word per line.
 */

int main(void)
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
            putchar('\n');
        else
            putchar(c);
    }
    return 0;
}
