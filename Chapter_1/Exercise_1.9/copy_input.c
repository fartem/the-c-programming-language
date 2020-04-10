#include <stdio.h>

#define BLANK ' '

/*
 * Write a Program to copy its input to its output,
 * replacing each string of one or more blanks by a single blank
 */

int main(void)
{
    char c;
    char last_c = '-';

    while ((c = getchar()) != EOF) {
        if (c == BLANK)
        {
            if (last_c != BLANK)
                putchar(c);
        }
        else
            putchar(c);

        last_c = c;
    }
    return 0;
}
