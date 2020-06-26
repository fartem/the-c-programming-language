#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/*
 * Write a cross-referencer that prints a list of all words
 * int a document, and on which it occurs. Remove noise words
 * like "the" and "and" so on.
 */

#define MAXWORD 1000
#define DEFAULT_COMP_LEN 8

struct tnode
{
	char *word;
	int count;
	struct linenumber *linenumbers;
	struct tnode *left;
	struct tnode *right;
};

struct linenumber
{
	int *number;
	struct linenumber *nextnumber;
};

struct simword
{
	char *word;
	int count;
	int linenumber;
	struct simword *nextword;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(const struct tnode *);
int get_word(char *, int, int *);
struct linenumber *lnumberalloc(void);
struct linenumber *addlinenumber(struct linenumber *, int);

int main(int argc, char *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int len;
	int lineno = 0;

	root = NULL;
	while (get_word(word, MAXWORD, &lineno) != 'x')
		if (isalpha(word[0]))
			root = addtree(root, word, lineno);

	if (argc == 1)
	{
		len = DEFAULT_COMP_LEN;
	}
	else if (argc == 2)
	{
		len = atoi(argv[1]);
	}
	else
	{
		printf("Incorrect number of argumets.\n");
		return 1;
	}

	printf("Words with line numbers:\n");
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *str_dup(char *);

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
		string = IN;

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
		{
			if (*w == '\\')
				*w++ = getch();
		}
		string = OUT;
		*w = '\0';
	}
	else if (directive == IN)
	{
		*w++ = c;
		while ((*w++ = getch()) != '\n')
		{
			if (c == '\\')
				*w++ = getch();
		}
		directive = OUT;
		*w = '\0';
	}
	return c;
}

struct tnode *addtree(struct tnode *p, char *w, int linenumber)
{
	int cond;
	if (p == NULL)
	{
		p = talloc();
		p->word = str_dup(w);
		p->count = 1;
		p->linenumbers = NULL;
		p->linenumbers = addlinenumber(p->linenumbers, linenumber);
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
	{
		p->count++;
		p->linenumbers = addlinenumber(p->linenumbers, linenumber);
	}
	else if (cond < 0)
	{
		p->left = addtree(p->left, w, linenumber);
	}
	else
	{
		p->right = addtree(p->right, w, linenumber);
	}
	return p;
}

struct linenumber *addlinenumber(struct linenumber *p, int linenumber)
{
	if (p == NULL)
	{
		p = lnumberalloc();
		p->number = linenumber;
		p->nextnumber = NULL;
	}
	else
	{
		p->nextnumber = addlinenumber(p->nextnumber, linenumber);
	}
	return p;
}

struct linenumber *lnumberalloc(void)
{
	return (struct linenumber *) malloc(sizeof(struct linenumber));
}

void treeprint(const struct tnode *p)
{
	if (p != NULL)
	{
		void printnumbers(const struct linenumber *);

		treeprint(p->left);
		printf("\n%s :", p->word);
		printnumbers(p->linenumbers);
		treeprint(p->right);
	}
}

void printnumbers(const struct linenumber *p)
{
	if (p != NULL)
	{
		printf("%d,", p->number);
		printnumbers(p->nextnumber);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *str_dup(char *s)
{
	char *p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);

	return p;
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

