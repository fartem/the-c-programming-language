#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write a loop equivalent for getline without using && and ||
 * This program prints the longest line in the given inputs
 */

int get_line(char s[], int limit);
void copy(char from[], char to[]);

int main(void)
{
    int length;
    int max = 0;

    char line[MAX_LENGTH];
    char max_line[MAX_LENGTH];

    while ((length = get_line(line, MAX_LENGTH)) > 0)
    {
        if (length > max)
        {
            max = length;
            copy(line, max_line);
        }
    }
    
    if (max > 0)
        printf("%s", max_line);

    return 0;
}

int get_line(char s[], int limit)
{
    int i, c;
    for (i = 0; i < limit - 1; i++)
    {
        c = getchar();
        if (c == EOF)
            break;
        if (c == '\n')
            break;
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
    while ((to[i] = from[i]) != '\0')
        i++;
}
