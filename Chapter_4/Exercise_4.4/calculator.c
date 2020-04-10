#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_OP 100
#define NUMBER 0

/*
 * Add the commands to print the top elements of the stack without popping,
 * to duplicate it, and to swap the top two elements. Add a command to clear the stack.
 */

int getop(char s[]);
void push(double d);
double pop(void);

int main(void)
{
    int type;
    double op1;
    double op2;
    char s[MAX_OP];

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
                push(pop() / op1);
            else
                printf("main: Error! Cannot delete by zero!");
            break;
        case '%':
            op1 = pop();
            if (op1 != 0.0)
                push(fmod(pop(), op1));
            else
                printf("main: Error! Cannot delete by zero!");
            break;
        case '?':
            op1 = pop();
            printf("\t%.8g\n", op1);
            push(op1);
            break;
        case 'c':
            clearsp();
            break;
        case 'd':
            op1 = pop();
            push(op1);
            push(op1);
            break;
        case 's':
            op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
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
        stack[sp++] = d;
    else
        printf("push: Error! Stack is full!");
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
    int i = 0, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

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
        ungetch(c);

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
        printf("ungetch: Error! Too many characters!");
    else
        buffer[buffer_position++] = c;
}
