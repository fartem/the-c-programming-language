#include <stdio.h>

/*
 * Write a function invert(x,p,n) that returns x with the n bits that begin
 * at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */

unsigned invert(unsigned x, int p, int n);

int main(void)
{
    printf("%u", invert((unsigned) 8, 3, 3));
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p + 1 - n));
}
