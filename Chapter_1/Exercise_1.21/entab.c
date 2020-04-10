#include <stdio.h>

#define TABSTOP 8

/*
 * Write a program entab that replaces strings of blanks by
 * the minimum number of tabs and blanks to achieve the same spacing.
 * Use the same tab stops as for detab. When either a tab or a single blank
 * would suffice to reach a tab stop, which should be given preference?
 */

int main(void) {
    char c;
    int b, t, position;
    for (position = 1; (c = getchar()) != EOF; position++) {
        if (c == ' ') {
            if (position % TABSTOP != 0)
            {
                b++;
            }
            else
            {
                b = 0;
                t++;
            }
        }
        else
        {
            for ( ; b > 0; b--)
                putchar('\t');

            if (c == '\t')
            {
                b = 0;
            }
            else
            {
                for ( ; b > 0; b--)
                    putchar(' ');
            }

            putchar(c);

            if (c == '\n')
                position = 0;
            else if (c == '\t')
                position = position + (TABSTOP - (position - 1) % TABSTOP) - 1;
        }
    }
    return 0;
}
