#include <stdlib.h>
#include <stdio.h>

/*
 * Write a function undef that will remove a name and definition
 * from the table maintained by lookup and install.
 */

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

struct nlist *lookup(char *);
char *strdup(char *);
struct nlist *install(char *, char *);
struct nlist *undef(char *);

static struct nlist *hashtab[HASHSIZE];

int main(int argc, char *argv[])
{
	struct nlist *table[4] = {
		(install("first_key", "first_value")),
		(install("second_key", "second_value")),
		(install("third_key", "third_value")),
		(install("fourth_key", "fourth_value"))
	};

	int i;
	for (i = 0; i < 4; i++)
		printf("%s->%s'\n", table[i]->name, table[i]->defn);

	undef("first_key");
	undef("third_key");

	struct nlist *result;

	char *keys[4] = {
		"first_key",
		"second_key",
		"third_key",
		"fourth_key"
	};

	for (i = 0; i < 4; i++)
	{
		if ((result = lookup(keys[i])) == NULL)
			printf("key not found\n");
		else
			printf("%s->%s\n", result->name, result->defn);
	}
	return 0;
}


unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

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

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

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

