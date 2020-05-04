#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
 * Make dcl recover from input errors.
 */

enum { NAME, PARENTS, BRACKETS };
enum { YES, NO };

void dcl(void);
void dirdcl(void);
void error(char *);

int gettoken(void);

int tokentype;
char token[];
char name[];
char out[];
int prevtoken = NO;

void dcl(void)
{
    int ns = 0;
    while (gettoken() == '*')
        ns++;
    
    dirdcl();

    while (ns-- > 0)
        strcat(out, "pointer to");
}

void dirdcl(void)
{
    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            error("error: missing )");
    }
    else if (tokentype == NAME)
    {
        strcpy(name, token);
    }
    else
    {
        error("error: expected name or (dsl)");
    }

    int type;
    while ((type = gettoken()) == PARENTS || type == BRACKETS)
    {
        if (type == PARENTS)
        {
            strcat(out, "function returning");
        }
        else
        {
            strcat(out, "array");
            strcat(out, token);
            strcat(out, "of");
        }
    }
}

void error(char *s)
{
    printf("%s\n", s);
    exit(1);
}

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
            return tokentype = PARENTS;
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
        error("too many characters in buffer!");
    else
        buffer[bufp++] = c;
}
