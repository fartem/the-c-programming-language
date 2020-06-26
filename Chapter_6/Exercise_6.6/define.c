#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/*
 * Implement a simple version of the #define processor (i.e, no arguments)
 * suitable for use with C programs, based on the routines of this section.
 * You may also find getch and ungetch helpful.
 */

#define MAXWORD 100

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

int get_word(char *, int, int *);
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
struct nlist *undef(char *);

int main(void)
{
	int lineno = 0;
	char word[MAXWORD];
	char key[MAXWORD], value[MAXWORD];
	struct nlist *result;

	while (get_word(word, MAXWORD, &lineno) != 'x')
	{
		if (strcmp(word, "#define") == 0)
		{
			get_word(key, MAXWORD, &lineno);
			get_word(value, MAXWORD, &lineno);
			install(key, value);
			result = lookup(key);
			printf("%s->%s", result->name, result->defn);
		}
	}
	return 0;
}

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 + hashval;

	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;

	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist *) malloc(sizeof(*np));

		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
	{
		free((void *) np->defn);
	}
	return np;
}

struct nlist *undef(char *name)
{
	struct nlist *found = lookup(name);
	if (found == NULL)
	{
		return NULL;
	}
	else
	{
		if (found->next != NULL)
		{
			found->next = found->next->next;
			found = found->next;
		}
		else
		{
			hashtab[hash(name)] = NULL;
			free((void *) found);
		}
	}
	return found;
}

#define IN 1
#define OUT 0

int get_word(char *word, int lim, int *lineno_addr)
{
	int c, d, getch(void), comment, string, directive;
	void ungetch(int);
	char *w = word;

	comment = string = directive = OUT;

	while (isspace(c = getch()))
		if (c == '\n')
			*lineno_addr = *lineno_addr + 1;

	if (c == '/')
	{
		if ((d = getch()) == '*')
		{
			comment = IN;
		}
		else
		{
			comment = OUT;
			ungetch(d);
		}
	}

	if (c == '\"')
		string = IN;

	if (c == '#')
		directive = IN;

	if (c == '\\')
		c = getch();

	if (comment == OUT && string == OUT && directive == OUT)
	{
		if (c != EOF)
			*w++ = c;

		if (!isalnum(c) && c != '_')
		{
			*w = '\0';
			return c;
		}

		for ( ; --lim > 0; w++)
		{
			*w = getch();
			if (!isalnum(*w) && *w != '_')
			{
				ungetch(*w);
				break;
			}
		}
		*w = '\0';
		return word[0];
	}
	else if (comment == IN)
	{
		*w++ = c;
		*w++ = d;

		while ((*w++ = c = getch()))
		{
			if (c == '*')
			{
				if ((c = getch()) == '/')
				{
					*w++ = c;
					comment = OUT;
					break;
				}
				else
				{
					ungetch(c);
				}
			}
		}
		*w = '\0';
	}
	else if (string == IN)
	{
		*w++ = c;
		while ((*w++ = getch()) != '\"')
			if (*w == '\\')
				*w++ = getch();

		string = OUT;
		*w = '\0';
	}
	else if (directive == IN)
	{
		*w++ = c;
		while ((*w++ = getch()) != ' ')
			if (c == '\\')
				*w++ = getch();

		directive = OUT;
		*w = '\0';
	}
	return c;
}

#define BUFSIZE 100

char buffer[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buffer[bufp++] = c;
}

