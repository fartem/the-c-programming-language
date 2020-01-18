#include <stdio.h>

#define MAXLINE 1000
#define LIMIT 80

/*
Write a program to print all input lines that are longer than 80 characters.
*/

int getln(char line[], int limit);

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getln(line, MAXLINE)) > 0)
    {
       if (len > LIMIT)
       {
           printf("Line: %s", line);
       }
    }
    return 0;
}

int getln(char line[], int limit)
{
    char c;
    int i = 0;

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