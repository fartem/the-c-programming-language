#include <stdio.h>
#include <stdlib.h>

#define MAX_OP 100
#define NUMBER '0'

/*
 * An alternate organization uses getline to read an entire input line;
 * this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
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

int get_line(char s[], int limit);

int li = 0;
char line[LINE_LENGTH];

int getop(char s[])
{
    int i, c;
    if (line[li] == '\0')
    {
        if (get_line(line, LINE_LENGTH) == 0)
            return EOF;
        else
            li = 0;
    }
    
    while ((s[0] = c = line[li++]) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = line[li++]))
            ;
    
    if (c == '.')
        while (isdigit(s[++i] = c = line[li++]))
            ;
    
    s[i] = '\0';
    li--;
    return NUMBER;
}

int get_line(char s[], int limit)
{
    int i, c;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}
