#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/*
 * Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
 */

void print_fahr_to_celsius_table();
void print_celsius_to_fahr_table();

int main()
{
    printf("Temperature Conversion Table\n");
    printf("1 - Fahrenheit to Celsius Table\n"); 
    printf("2 - Celsius to Fahrenheit Table\n");
    printf("Enter number: ");

    char c = getchar();

    if (c == '1')
    {
        print_fahr_to_celsius_table();
    }
    else if (c == '2')
    {
        print_celsius_to_fahr_table();
    }
    else
    {
        return -5;
    }
    return 0;
}

void print_fahr_to_celsius_table()
{
    float fahr, celsius;

    for (fahr = LOWER; fahr <= UPPER; fahr += STEP)
    {
        printf("%3.0f %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
    }
}

void print_celsius_to_fahr_table()
{
    float fahr, celsius;

    for (celsius = LOWER; celsius <= UPPER; celsius += STEP)
    {
        printf("%3.0f %6.1f\n", celsius, celsius * (5.0 / 9.0) + 32);
    }
}
