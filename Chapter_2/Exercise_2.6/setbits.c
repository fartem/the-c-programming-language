#include <stdio.h>

/*
 * Write a function setbits(x,p,n,y) that returns x with the n bits that begin
 * at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 */

unsigned setBits(unsigned x, int p, int n, unsigned y);

int main(void)
{
    printf("%u", setBits((unsigned) 12, 3, 2, (unsigned) 57));
    return 0;
}

unsigned setBits(unsigned x, int p, int n, unsigned y)
{
    return x & ~(~(~0 << n) << (p + 1 - n)) | (y & ~(~0 << n)) << (p + 1 - n);
}
