#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 100
#define MAX_LINE 100

/*
 * Write a routine ungets(s) that will push back an entire string onto the input.
 * Should ungets know about buf and bufp, or should it just use ungetch?
 */

int bufp = 0;
int buffer[MAX_BUFFER];

int getch(void);
void ungetch(int c);
void ungets(char s[]);
int getLine(char s[], int limit);

int main(void)
{
    char line[MAX_LINE];
    int c;

    getLine(line, MAX_LINE);
    ungets(line);

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

int getLine(char s[], int limit)
{
    int c, i;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
}

void ungets(char s[])
{
    int i = strlen(s);
    while (i > 0)
    {
        ungetch(s[--i]);
    }
}

void ungetch(int c)
{
    if (bufp > MAX_BUFFER)
        printf("ungetch: Error! Too many characters in buffer!");
    else
        buffer[bufp++] = c;
}

int getch()
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}
