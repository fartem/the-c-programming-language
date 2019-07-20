#include <stdio.h>

/*
Write a program to print the corresponding Celsius to Fahrenheit table.
*/

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = -50;
    upper = 50;
    step = 5;

    celsius = lower;

    printf("Temperature table:\n");
    while (celsius <= upper)
    {
        fahr = celsius * (5.0 / 9.0) + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}