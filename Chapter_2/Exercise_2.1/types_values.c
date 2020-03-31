#include <stdio.h>

/*
 * Write a program to determine the ranges of char, short, int, and long variables,
 * both signed and unsigned, by printing appropriate values from standard headers
 * and by direct computation. Harder if you compute them: determine the ranges
 * of the various floating-point types.
 */

int main()
{
    printf("Minimum signed char: %d\n", -(char) ((unsigned char) ~0 >> 1) - 1);
    printf("Maximum signed char: %d\n", (char) ((unsigned char) ~0 >> 1));

    printf("Minimum signed short: %d\n", -(short) ((unsigned short) ~0 >> 1) - 1);
    printf("Maximum signed short: %d\n", (short) ((unsigned short) ~0 >> 1));

    printf("Minimum signed int: %d\n", -(int) ((unsigned int) ~0 >> 1) - 1);
    printf("Maximum signed int: %d\n", (int) ((unsigned int) ~0 >> 1));

    printf("Minimum signed long: %ld\n", -(long) ((unsigned long) ~0 >> 1) - 1);
    printf("Maximum signed long: %ld\n", (long) ((unsigned long) ~0 >> 1));

    printf("Maximum unsigned char: %d\n", (unsigned char) ~0);
    printf("Maximum unsigned short: %d\n", (unsigned short) ~0);
    printf("Maximum unsigned int: %u\n", (unsigned int) ~0);
    printf("Maximum unsigned long: %lu\n", (unsigned long) ~0);

    return 0;
}
