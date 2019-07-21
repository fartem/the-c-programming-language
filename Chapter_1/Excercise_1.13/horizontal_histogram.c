#include <stdio.h>

/*
Write a program to print a histogram of the lengths of words in its input.
It is easy to draw the histogram with the bars horizontal.
*/

int main()
{
    char c;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            putchar('\n');
        }
        else
        {
            putchar('*');
        }
    }

    return 0;
}