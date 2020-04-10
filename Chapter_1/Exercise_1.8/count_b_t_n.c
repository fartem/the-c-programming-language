#include <stdio.h>

/*
 * Write a program to count blanks, tabs and newlines
 */

int main(void)
{
    int blanks = 0;
    int tabs = 0;
    int new_lines = 0;

    char c;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            blanks++;
        else if (c == '\t')
            tabs++;
        else if (c == '\n')
            new_lines++;
    }

    printf("Blanks: %d\nTabs: %d\nNew lines: %d", blanks, tabs, new_lines);
    return 0;
}