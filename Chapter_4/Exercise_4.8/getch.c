#include <stdio.h>

/*
 * Suppose that there will never be more than one character of pushback.
 * Modify getch and ungetch accordingly.
 */

char buf = 0;

int getch(void);
void ungetch(int c);

int main(void)
{
    int c = '!';
    ungetch(c);
    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}

int getch(void)
{
    int c;
    if (buf != 0)
        c = buf;
    else
        c = getchar();
    
    buf = 0;
    return c;
}

void ungetch(int c)
{
    if (buf != 0)
        printf("ungetch: Error! Too many characters!");
    else
        buf = c;
}
