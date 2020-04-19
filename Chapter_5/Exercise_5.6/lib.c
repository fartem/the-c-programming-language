#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAX_VAL 100
#define BUFFER_SIZE 100
#define LINE_LENGTH 1000
#define MAX_OP 100

/*
 * Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of array indexing. Good possibilities
 * include getline (Chapters 1 and 4), atoi, itoa,
 * and their variants (Chapters 2, 3, and 4), reverse (Chapter 3),
 * and strindex and getop (Chapter 4).
 */

int getch(void);
void ungetch(int);
int getop(char *);
void push(double);
double pop(void);

int get_line(char *, int limit);
int str_index(char *, char *);
int a_to_i(char *);
void i_to_a(int, char *);
void reverse(char *);

int sp = 0;
int bufp = 0;
double val[MAX_VAL];
char buffer[BUFFER_SIZE];

char pattern[] = "PATTERN";

int main()
{
    char line[LINE_LENGTH];
    int found = 0;

    while ((get_line(line, LINE_LENGTH)) > 0)
        if (str_index(line, pattern) >= 0)
            found++;
    
    printf("%d\n", found);

    char *s = "1234";
    int ret;

    ret = a_to_i(s);
    printf("%d\n", ret);

    char s1[100];
    int i = 12345;
    i_to_a(i, s1);
    reverse(s1);
    printf("%s\n", s1);

    char *s2 = "This is a line";
    char *t = "is";
    ret = 0;
    ret = str_index(s2, t);
    printf("%d\n", ret);

    int type;
    double op;
    char s3[LINE_LENGTH];

    while ((type = getop(s3)) != EOF)
    {
        switch (type)
        {
            case NUMBER:
                push(atof(s3));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op = pop();
                push(pop() - op);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op = pop();
                if (op != 0.0)
                    push(pop() / op);
                else
                    printf("Error! Cannot delete by zero!");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("Error! Unknown operation: %s\n", s3);
                break;
        }
    }

    return 0;
}

int get_line(char *s, int limit)
{
    int c;
    char *t = s;

    while (--limit > 0 && (c = getchar()) != 'X' && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return s - t;
}

int str_index(char *s, char *t)
{
    char *b = s;
    char *p, *r;
    
    for (; *s != '\0'; s++)
    {
        for (p = s, r = t; *r != '\0' && *p == *r; p++, r++)
            ;
        
        if (r > t && *r == '\0')
            return s - b;
    }
    return -1;
}

int a_to_i(char *s)
{
    int n = 0;
    int sign;

    for (; isspace(*s); s++)
        ;
    
    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    for (; isdigit(*s); s++)
        n = 10 * n + *s - '0';

    return sign * n;    
}

void i_to_a(int n, char *s)
{
    int sign;
    char *t = s;

    if ((sign = n) < 0)
        n = -n;
    
    do
    {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';
    
    *s = '\0';
}

void reverse(char *s)
{
    int c;
    char *t;

    for (t = s + (strlen(s) - 1); s < t; s++, t--)
    {
        c = *s;
        *s = *t;
        *t = c;
    }
}

void push(double d)
{
    if (sp < MAX_VAL)
        val[sp++] = d;
    else
        printf("push: Error! Stack is full!");
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
        printf("pop: Error! Stack is empty!");

    return 0.0;
}

int getop(char *s)
{
    int c;

    while ((*s = c = getchar()) == ' ' || c == '\t')
        ;
    
    *(s + 1) = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(*++s = c = getchar()))
            ;
    
    if (c == '.')
        while (isdigit(*++s = c = getchar()))
            ;
        
    *s = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int i)
{
    if (bufp < BUFFER_SIZE)
        buffer[bufp++] = i;
    else
        printf("ungetch: Error! Buffer is full!");
}
