#include <stdio.h>
#include <stdlib.h>

/*
 * Functions like isupper can be implemented to save space
 * or to save time. Explore both possibilities.
 */

int is_upper(int);

int main(void)
{
	int c;
	while ((c = getchar()) != 'x')
	{
		if (c == '\n')
			continue;

		if (is_upper(c) == 1)
			printf("true\n");
		else
			printf("false\n");
	}
	return EXIT_SUCCESS;
}

int is_upper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;

	return 0;
}

