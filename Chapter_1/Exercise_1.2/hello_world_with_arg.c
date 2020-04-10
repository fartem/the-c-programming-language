#include <stdio.h>

/*
 * Experiment to find out what happens when prints's argument string contains \c, where c is some
 * character not listed above.
 */

int main(void)
{
    printf("Hello World!\c");
	return 0;
}
