#include <stdio.h>

#define MAX_LINE 1000

/*
 * Write a loop equivalent for getline without using && and ||
 * This program prints the longest line in the given inputs
 */

int getLine(char s[], int limit);
void copy(char from[], char to[]);

int main()
{
    int length;
    int max = 0;

    char line[MAX_LINE];
    char maxLine[MAX_LINE];

    while ((length = getLine(line, MAX_LINE)) > 0)
    {
        if (length > max)
        {
            max = length;
            copy(line, maxLine);
        }
    }
    
    if (max > 0)
    {
        printf("%s", maxLine);
    }
    return 0;
}

int getLine(char s[], int limit)
{
    int i;
    int c;

    for (i = 0; i < limit - 1; i++)
    {
        c = getchar();
        if (c == EOF)
        {
            break;
        }
        if (c == '\n')
        {
            break;
        }
        s[i] = c;
    }
    
    if (c == '\n')
    {
        s[i] = c;
        i++;
    }
    
    s[i] = '\0';
    return i;
}

void copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}
