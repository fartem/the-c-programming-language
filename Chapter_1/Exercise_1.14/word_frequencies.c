#include <stdio.h>

#define CHARS 128

/*
 * Write a program to print a histogram of the frequencies of different characters in its input.
 */

int main(void)
{
    int characters[CHARS];

    char c;
    for (int i = 0; i < CHARS; i++)
        characters[i] = 0;

    while ((c = getchar()) != EOF)
        characters[c]++;
    
    for (int i = 0; i < CHARS; i++)
    {
        putchar(i);
        putchar(':');
        putchar(' ');

        for (int j = 0; j < characters[i]; j++)
            putchar('*');

        putchar('\n');
    }
    return 0;
}
