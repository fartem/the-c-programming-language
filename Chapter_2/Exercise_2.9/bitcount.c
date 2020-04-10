#include <stdio.h>

/*
 * In a two’s complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
 * Explain why. Use this observation to write a faster version of bitcount.
 */

int bitCount(unsigned x);

int main(void)
{
    printf("%d\n", bitCount((unsigned) 5));
    return 0;
}

int bitCount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= x - 1)
    {
        b++;
    }
    return b;
}
