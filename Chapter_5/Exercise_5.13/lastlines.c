#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Write the program tail, which prints
 * the last n lines of its input.
 */

#define DEF_LINES 10
#define LINES 100
#define LINE_LENGTH 100

void error(char *);
int get_line(char *, int);

int main(int argc, char *argv[])
{
    char *p;
    char *buf;
    char *bufend;

    char line[LINE_LENGTH];
    char *lineptr[LINES];

    int first, i, last, len, n, nlines;

    if (argc == 1)
        n = DEF_LINES;
    else if (argc == 2 && (*++argv)[0] == '-')
        n = atoi(argv[0] + 1);
    else
        error("Usage: tail [-n]\n");

    if (n < 1 || n > LINES)
        n = LINES;

    for (i = 0; i < LINES; i++)
        lineptr[i] = NULL;
    
    if ((p = buf = malloc(LINES * LINE_LENGTH)) == NULL)
        error("error: cannot allocate buffer!");
    
    bufend = buf + LINES + LINE_LENGTH;

    last = 0;
    nlines = 0;

    while ((len = get_line(line, LINE_LENGTH)) > 1)
    {
        if (p + len + 1 >= bufend)
            p = buf;
        
        lineptr[last] = p;

        strcpy(lineptr[last], line);

        if (++last >= LINES)
            last = 0;
        
        p += len + 1;
        nlines++;
    }

    if (n > nlines)
        n = nlines;

    first = last - n;

    if (first < 0)
        first += LINES;

    for (i = first; n-- > 0; i = (i + 1) % LINES)
        printf("%s", lineptr[i]);

    return 0;
}

void error(char *s)
{
    printf("%s\n", s);
    exit(1);
}

int get_line(char s[], int limit)
{
    int c, i;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}
