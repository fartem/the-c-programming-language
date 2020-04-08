#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OP 100
#define NUMBER 0

/*
 * Given the basic framework, it’s straightforward to extend the calculator.
 * Add the modulus (%) operator and provisions for negative numbers.
 */

int getop(char s[]);
void push(double d);
double pop();

int main()
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
            {
                push(pop() / temp_op);
            }
            else
            {
                printf("main: Error! Cannot delete by zero!");
            }
            break;
        case '%':
            temp_op = pop();
            if (temp_op != 0.0)
            {
                push(fmod(pop(), temp_op));
            }
            else
            {
                printf("main: Error! Cannot delete by zero!");
            }
            break;
        case '\n':
            printf("\t%.8g\n", pop());
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
