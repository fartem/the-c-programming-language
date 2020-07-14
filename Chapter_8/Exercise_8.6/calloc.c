#include <stdio.h>
#include <stdlib.h>

/*
 * The standard library function calloc(n, size) returns a pointer to n objects
 * of size size, with the storage initialized to zero. Write calloc, by calling
 * malloc or by modifying it.
 */

char *c_alloc(unsigned, unsigned);

int main(int argc, char *argv[])
{
	char *p = NULL;
	
	p = c_alloc(100, sizeof *p);
	if (p == NULL)
	{
		printf("c_alloc returned NULL");
	}
	else
	{
		for (int i = 0; i <= 100; i++)
		{
			printf("%08X", p[i]);
			if (i % 8 == 7)
				printf("\n");
		}
		printf("\n");
		free(p);
	}
	return 0;
}

char *c_alloc(unsigned n, unsigned size)
{
	unsigned nb;
	char *p, *q;

	nb = n * size;

	if ((p = q = malloc(nb)) != NULL)
		for (int i = 0; i < nb; i++)
			*p++ = 0;
	return q;
}

