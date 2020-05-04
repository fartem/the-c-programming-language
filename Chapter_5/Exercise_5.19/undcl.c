#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Modify undcl so that it does not add redundant parentheses to declarations.
 */

#define MAX_TOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);

int gettoken(void);
int nexttoken(void);

int tokentype;
char token[MAX_TOKEN];
char out[1000];

int main(int argc, char *argv[])
{
    int type;
    char temp[MAX_TOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
        {
            if (type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if (type == '*')
            {
                if ((type = nexttoken() == PARENS || type == BRACKETS))
                {
                    sprintf(temp, "(%s)", out);
                }
                else
                {
                    sprintf(temp, "*%s", out);
                }
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
            }
            else
            {
                printf("error: invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

enum { YES, NO };

int prevtoken = NO;

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);

    char *p = token;

    if (prevtoken == YES)
    {
        prevtoken = NO;
        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;
    
    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != '[';)
            *p++ = c;
        
        *p = '\0';

        ungetch(c);
        return tokentype = NAME;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalpha(c = getch());)
            *p++ = c;

        *p = '\0';

        ungetch(c);
        return tokentype = NAME;
    }
    else
    {
        return tokentype = c;
    }
}

int nexttoken(void)
{
    int type = gettoken();
    prevtoken = YES;
    return type;
}

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
char bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp > BUFFER_SIZE)
        printf("too many characters in buffer!");
    else
        buffer[bufp++] = c;
}
