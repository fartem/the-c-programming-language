#include <stdio.h>
#include <stdlib.h>

/*
 * Write the program expr, which evaluates a reverse
 * Polish expression from the command line,
 * where each operator or operand is a separate argument.
 */

#define MAX_OP 100
#define NUMBER '0'

int getop(char []);
void ungets(char []);
void push(double);
double pop(void);

int main(int argc, char *argv[])
{
    char s[MAX_OP];
    double op2;

    while (--argc > 0)
    {
        ungets(" ");
        ungets(*++argv);

        switch (getop(s))
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: cannote delete by zero!\n");
                break;
            default:
                printf("error: unknown command!\n");
                argc = 1;
                break;
        }
    }
    printf("Result: %8g\n", pop());
    return 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;
    
    int i = 0;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    
    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
int bufp  = 0;

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFFER_SIZE)
        printf("error: too many characters in buffer!\n");
    else
        buffer[bufp++] = c;
}

#define MAX_VAL 100

int sp = 0;
double val[MAX_VAL];

void push(double d)
{
    if (sp < MAX_VAL)
        val[sp++] = d;
    else
        printf("error: stack is full!\n");
}

double pop()
{
    if (sp > 0)
        return val[--sp];
    else
        printf("error: stack is empty!\n");
    
    return 0.0;
}

#include <string.h>

void ungets(char s[])
{
    int len = strlen(s);
    void ungetch(int);

    while (len > 0)
        ungetch(s[--len]);
}
