#include <stdio.h>

#define MAXLINE 1000

/*
 * Revise the main routine of the longest-line program so it will correctly print
 * the length of arbitrary long input lines, and as much as possible of the text.
 */

int getln(char line[], int limit);
void copy(char from[], char to[]);

int main(void)
{
    int len, max;
    char line[MAXLINE], longest[MAXLINE];

    max = 0;
    while ((len = getln(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(line, longest);
        }
        printf("Line_length: %d\n", len);
    }

    if (max > 0)
        printf("Longest: %s", longest);

    return 0;
}

int getln(char line[], int limit)
{
    char c, i;;
    for (i = 0; i < limit - 1 && ((c = getchar()) != EOF && c != '\n'); i++)
        line[i] = c;

    if (c == 'n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

void copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        i++;
}
