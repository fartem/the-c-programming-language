#include <stdio.h>

/*
 * Verify the expression getchar() != EOF is 0 or 1.
 */

int main(void)
{
    printf("Value of expression: %d", getchar() != EOF);
    return 0;
}
