#include <stdio.h>
#include <stdlib.h>

#define MAX_OP 100
#define NUMBER '0'

/*
 * Modify getop so that it doesn’t need to use ungetch.
 * Hint: use an internal static variable.
 */

int getop(char s[]);
void push(double d);
double pop(void);

int main(void)
{
    int type;
    double temp_op;
    char s[MAX_OP];

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            temp_op = pop();
            push(pop() - temp_op);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            temp_op = pop();
            if (temp_op != 0.0)
                push(pop() / temp_op);
            else
                printf("main: Error! Cannot delete by zero!");
            break;
        case '\n':
            printf("\t%.9g\n", pop());
            break;
        default:
            printf("main: Error! Unknown command: %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAX_VAL 100

int sp = 0;
int stack[MAX_VAL];

void push(double d)
{
    if (sp < MAX_VAL)
        stack[sp++] = d;
    else
        printf("push: Error! Stack is full! Cannot push %g\n", d);
}

double pop(void)
{
    if (sp > 0)
    {
        return stack[--sp];
    }
    else
    {
        printf("pop: Error! Stack is empty!");
        return 0.0;
    }
}

#include <ctype.h>

#define LINE_LENGTH 1000

int getch(void);

int getop(char s[])
{
    int i, c;
    static int lastc = 0;
    if (lastc == 0)
    {
        c = getch();
    }
    else
    {
        c = lastc;
        lastc = 0;
    }
    
    while ((s[0] = c) == ' ' || c == '\t')
        c = getch();

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    
    s[i] = '\0';
    return NUMBER;
}

#define BUFFER_SIZE 100

int bufp = 0;
char buffer[BUFFER_SIZE];

int getch(void)
{
    return (bufp > 0) ? buffer[--bufp] : getchar();
}
