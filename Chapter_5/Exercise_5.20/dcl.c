#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Expand dcl to handle declarations with function argument types,
 * qualifiers like const, and so on.
 */

enum { NAME, PARENS, BRACKETS };
enum { YES, NO };

void dcl(void);
void dirdcl(void);
void error(char *);

int gettoken(void);

int tokentype;
char token[];
char name[];
char datatype[];
char out[];
int prevtoken;

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
    int type;
    void parmdcl(void);

    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            error("error: missing )");
    }
    else if (tokentype == NAME)
    {
        if (name[0] == '\0')
            strcpy(name, token);
    }
    else
    {
        prevtoken = YES;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
    {
        if (type == PARENS)
        {
            strcat(out, "function returning");
        }
        else if (type == '(')
        {
            strcat(out, "function expecting");
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

#define MAX_TOKEN 100

void dclspec(void);
int typespec(void);
int typeequal(void);

int compare(char **, char **);

void parmdcl(void)
{
    do
    {
        dclspec();
    } while (tokentype != ')');

    if (tokentype != ')')
        error("error: missing ) in parameter declaration");
}

void dclspec(void)
{
    char temp[MAX_TOKEN];

    temp[0] = '\0';
    gettoken();

    do
    {
        if (tokentype != NAME)
        {
            prevtoken = YES;
            dcl();
        }
        else if (typespec() == YES || typequal() == YES)
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else
        {
            error("error: unknown type in parameters list");
        }
    } while (tokentype != ',' && tokentype != ')');

    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

int typespec(void)
{
    static char *types[] =
    {
        "char",
        "int",
        "void"
    };

    char *pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *), compare) == NULL)
        return NO;
    else
        return YES;
}

int typeequal(void)
{
    static char *types[] =
    {
        "const",
        "volatile"
    };

    char *pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *), compare) == NULL)
        return NO;
    else
        return YES;
}

int compare(char **s, char **t)
{
    return strcmp(s, t);
}
