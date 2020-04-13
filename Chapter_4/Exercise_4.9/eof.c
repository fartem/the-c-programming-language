#include <stdio.h>

#define BUFFER_LIMIT 100

/*
 * Our getch and ungetch do not handle a pushed-back EOF correctly.
 * Decide what their properties ought to be if an EOF is pushed back,
 * then implement your design.
 */

char bufp = 0;
char buffer[BUFFER_LIMIT];

int getch(void);
void ungetch(int c);

int main()
{
    int c = '!';
    ungetch(c);
    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int i)
{
    if (bufp < 100)
        buffer[bufp++] = i;
    else
        printf("ungetch: Error! Too many characters in buffer!");
}
