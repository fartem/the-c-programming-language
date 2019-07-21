#include <stdio.h>

#define MAXLINE 1000

/*
Write a program to remove trailing blanks and tabs
from each line of input, and to delete entirely blank lines.
*/

int getln(char line[], int limit);
int remove_trail(char line[], int len);

int main()
{
    int len;

    char line[MAXLINE];

    while ((len = getln(line, MAXLINE)) > 0)
    {
        if (remove_trail(line, len) > 0)
        {
            printf("Line: %s", line);
        }
    }

    return 0;
}

int getln(char line[], int limit)
{
    char c;
    int i;
    
    for (i = 0; i < limit - 1 && ((c = getchar()) != EOF && c != '\n'); i++)
    {
        line[i] = c;
    }

    if (c == 'n')
    {
        line[i] = c;
        i++;
    }

    line[i] = '\0';

    return i;
}

int remove_trail(char line[], int len)
{
    int i;

    for (i = len - 2; ((line[i] == ' ') || (line[i] == '\t')); i--)
        ;

    if (i >= 0)
    {
        i++;
        line[i] = '\n';
        i++;
        line[i] = '\0';
    }

    return i;
}