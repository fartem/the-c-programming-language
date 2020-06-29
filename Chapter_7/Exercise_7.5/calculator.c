#include <stdio.h>
#include <stdlib.h>

/*
 * Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion.
 */

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

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
					printf("error: zero divisor\n");
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
		printf("error: stack empty\n");

	return 0.0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;

	s[1] = '\0';

	i = 0;
	if (!isdigit(c) && c != '.' && c != '-')
		if (isdigit(c = getch()) || c == '.')
		{
			s[++i] = c;
		}
		else
		{
			if (c != EOF)
				ungetch(c);
			return '-';
		}

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

#define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0;

int getch(void)
{
	char c;
	if (bufp > 0)
		return buffer[--bufp];
	else
		scanf("%c", &c);

	return c;
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buffer[bufp++] = c;
}

