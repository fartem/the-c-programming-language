#include <stdio.h>

#define MAXLINE 1000
#define TABWIDTH 8

/*
 * Write a program detab that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop.
 * Assume a fixed set of tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 */

int getln(char line[], int limit);
void detab(char line[], char tab_line[]);

int main()
{
    char line[MAXLINE];
    char tab_line[MAXLINE];

    getln(line, MAXLINE);
    detab(line, tab_line);
    printf("Output: %s", tab_line);
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

void detab(char line[], char tab_line[])
{
    int i, j;
    int spacew;

    i = j = 0;

    while (line[i] != '\0')
    {
        // Get spaces for current index:
        spacew = TABWIDTH - j % TABWIDTH;

        if (line[i] == '\t')
        {
            while (spacew-- > 0)
            {
                tab_line[j++] = '#';
            }
            i++;
        }
        else
        {
            tab_line[j++] = line[i++];
        }
    }
    
    if (line[i] == '\n')
    {
        tab_line[j++] = line[i];
    }
    
    tab_line[j] = '\0';
}
