#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
 * Modify the pattern finging program of Chapter 5 to take its input from
 * a set of named files or, if no files are names arguments, from the standard
 * input. Should the file name be printed when a matching line is found?
 */

#define MAXLINE 1000

int get_line(char *, int);
int strindex(char *, char *);

char pattern[] = "ould";

int main(void)
{
	char line[MAXLINE];
	int found = 0;

	while ((get_line(line, MAXLINE)) > 0)
		if (strindex(line, pattern) >= 0)
		{
			printf("%s\n", line);
			found++;
		}

	return 0;
}

int get_line(char *s, int lim)
{
	int c;
	char *t = s;

	while (--lim > 0 && (c = getchar()) != 'X' && c != '\n')
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';
	return s - t;
}

int strindex(char *s, char *t)
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

