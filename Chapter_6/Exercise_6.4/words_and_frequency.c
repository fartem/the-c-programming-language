#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

/*
 * Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurrence. Precede each word
 * by its count.
 */

#define MAXWORD 1000

struct tnode
{
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct numwordnode
{
	int number;
	struct words *wordslist;
	struct numwordnode *left;
	struct numwordnode *right;
};

struct words
{
	char *word;
	struct words *nextword;
};

struct tnode *addtree(struct tnode *, char *);
struct numwordnode *addnumtree(struct numwordnode *, int, char *);
struct words *addwordtolist(struct words*, char *);
void printwords(const struct words*, const int);

struct numwordnode *traverse(const struct tnode *, struct numwordnode *);
void treeprint(const struct numwordnode *);
int get_word(char *, int);

int main(int argc, char *argv[])
{
	struct tnode *root;
	struct numwordnode *numwordroot;

	char word[MAXWORD];

	root = NULL;
	numwordroot = NULL;
	while (get_word(word, MAXWORD) != 'x')
		if (isalpha(word[0]))
			root = addtree(root, word);

	numwordroot = traverse(root, numwordroot);
	printf("Words and their frequencies:\n");
	treeprint(numwordroot);
	return 0;
}

struct tnode *talloc(void);
struct numwordnode *numwordalloc(void);
struct words *wordsalloc(void);
char *str_dup(char *);

#define IN 1
#define OUT 0

int get_word(char *word, int lim)
{
	int c, d, getch(void), comment, string, directive;
	void ungetch(int);
	char *w = word;

	comment = string = directive = OUT;

	while (isspace(c = getch()))
		;

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

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL)
	{
		p = talloc();
		p->word = str_dup(w);
		p->count = 1;
		p->left = p->right = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	
	return p;
}

struct numwordnode *addnumtree(struct numwordnode *p, int count, char* w)
{
	if (p == NULL)
	{
		p = numwordalloc();
		p->number = count;
		p->wordslist = NULL;
		p->wordslist = addwordtolist(p->wordslist, w);
	}
	else if (count < p->number)
	{
		p->left = addnumtree(p->left, count, w);
	}
	else
	{
		p->right = addnumtree(p->right, count, w);
	}
	return p;
}

struct words *addwordtolist(struct words* list, char *w)
{
	if (list == NULL)
	{
		list = wordsalloc();
		list->word = str_dup(w);
		list->nextword = NULL;
	}
	else
	{
		list->nextword = addwordtolist(list->nextword, w);
	}
}

void treeprint(const struct numwordnode *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printwords(p->wordslist, p->number);
		treeprint(p->right);
	}
}

void printwords(const struct words* w, const int count)
{
	if (w != NULL)
	{
		printf("%s->%d\n", w->word, count);
		w = w->nextword;
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct numwordnode *traverse(const struct tnode *p, struct numwordnode *q)
{
	if (p != NULL)
	{
		q = traverse(p->left, q);
		q = addnumtree(q, p->count, p->word);
		q = traverse(p->right, q);
	}
	return q;
}

struct numwordnode *numwordalloc(void)
{
	return (struct numwordnode *) malloc(sizeof(struct numwordnode));
}

struct words *wordsalloc(void)
{
	return (struct words *) malloc(sizeof(struct words));
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

