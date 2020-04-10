#include <stdio.h>

/*
 * Write a function rightrot(x,n) that returns the value
 * of the integer x rotated to the right by n positions.
 */

unsigned rightRot(unsigned x, int n);

int main(void)
{
    printf("%u", rightRot((unsigned) 8, 1));
    return 0;
}

unsigned rightRot(unsigned x, int n)
{
    unsigned r;
    r = x << (wordLength() - n);
    x = x >> n;
    x = x | r;
    return x;
}

int wordLength()
{
    int i;
    unsigned v = (unsigned) ~0;
    for (i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}
