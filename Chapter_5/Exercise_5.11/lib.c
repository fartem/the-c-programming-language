#include <stdio.h>
#include <stdlib.h>

/*
 * Modify the program entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments. Use the default tab settings
 * if there are no arguments.
 */

#define MAX_LINE 100
#define TABINC 8
#define YES 1
#define NO 0

void esettab(int, char *[], char *);
void detab(char *);

int main(int argc, char *argv[])
{
    char tab[MAX_LINE + 1];
    esettab(argc, argv, tab);
    detab(tab);
    return 0;
}

void esettab(int argc, char *argv[], char *tab)
{
    int i, inc, pos;
    if (argc <= 1)
    {
        for (i = 1; i <= MAX_LINE; i++)
            tab[i] = (i % TABINC == 0) ? YES : NO;
    }
    else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+')
    {
        pos = atoi(&(*++argv)[1]);
        inc = atoi(&(*++argv)[1]);

        for (i = 1; i <= MAX_LINE; i++)
        {
            if (i != pos)
            {
                tab[i] = NO;
            }
            else
            {
                tab[i] = YES;
                pos += inc;
            }
        }
    }
    else
    {
        for (i = 1; i <= MAX_LINE; i++)
            tab[i] = NO;

        while (--argc > 0)
        {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAX_LINE)
                tab[pos] = YES;
        }
    }
}

void detab(char *tab)
{
    int tabpos(int, char *);

    int c, pos = 1;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            do
            {
                putchar(' ');
            } while (tabpos(pos++, tab) != YES);
        }
        else if (c == '\n')
        {
            putchar(c);
            pos = 1;
        }
        else
        {
            putchar(c);
            pos++;
        }
    }
}

int tabpos(int pos, char *tab)
{
    return (pos > MAX_LINE) ? YES : tab[pos];
}
