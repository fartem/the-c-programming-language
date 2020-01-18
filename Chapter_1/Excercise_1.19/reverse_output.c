#include <stdio.h>

#define MAXLINE 1000

/*
Write a function reverse(s) that reverses the character string s.
Use it to write a program that reverses its input a line at a time.
*/

int getln(char line[], int limit);
void reverse(char line[]);
void clean(char line[]);

int main()
{
    char line[MAXLINE];

    while (getln(line, MAXLINE) > 0)
    {
        reverse(line);
        printf("Output: %s\n", line);
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

void reverse(char line[])
{
    int i;

    for (i = 0; line[i] != '\0'; i++)
        ;
    
    i--;

    if (line[i] == '\n')
    {
        i--;
    }
    
    int j = 0;
    int temp;

    while (i > j)
    {
        temp = line[j];
        line[j] = line[i];
        line[i] = temp;
        j++;
        i--;
    }
}