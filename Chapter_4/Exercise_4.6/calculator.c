#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OP 100
#define NUMBER 0

/*
 * Add commands for handling variables. (It’s easy to provide twenty-six variables with single-letter names.)
 * Add a variable for the most recently printed value.
 */

int getop(char s[]);
void push(double d);
double pop();

int main()
{
    int type;
    int var = 0;
    double op1;
    double v;
    char s[MAX_OP];
    double variables[26];

    void clearsp();

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
            op1 = pop();
            push(pop() - op1);
            break;
        case '*':
            push(pop() * pop());
            break;
        case '/':
            op1 = pop();
            if (op1 != 0.0)
            {
                push(pop() / op1);
            }
            else
            {
                printf("main: Error! Cannot delete by zero!");
            }
            break;
        case '=':
            pop();
            if (var >= 'A' && var <= 'Z')
            {
                variables[var - 'A'] = pop();
            }
            else
            {
                printf("main: Error! Unknown variable name: %s\n", s);
            }
            break;
        case '\n':
            v = pop();
            printf("\t%.8g\n", v);
            break;
        default:
            if (type >= 'A' && type <= 'Z')
            {
                push(variables[type - 'A']);
            }
            else if (type == 'v')
            {
                 push(v);
            }
            else
            {
                printf("main: Error! Unknown command: %s\n", s);
            }
            break;
        }
        var = type;
    }
    return 0;
}

#define MAX_VAL 100

int sp = 0;
double stack[MAX_VAL];

void push(double d)
{
    if (sp < MAX_VAL)
    {
        stack[sp++] = d;
    }
    else
    {
        printf("push: Error! Stack is full!");
    }
}

double pop()
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

void clearsp()
{
    sp = 0;
}

#include <ctype.h>

int getch();
void ungetch(int c);

int getop(char s[])
{
    int i = 0;
    int c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
    {
        return c;
    }

    if (c == '-')
    {
        if (isdigit(c = getch()) || c == '.')
        {
            s[++i] = c;
        }
        else
        {
            if (c != EOF)
            {
                ungetch(c);
                return '-';
            }
        }
    }
    
    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }
    
    if (c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];
int buffer_position = 0;

int getch()
{
    return (buffer_position > 0) ? buffer[--buffer_position] : getchar();
}

void ungetch(int c)
{
    if (buffer_position >= BUFFER_SIZE)
    {
        printf("ungetch: Error! Too many characters!");
    }
    else
    {
        buffer[buffer_position++] = c;
    }
}
