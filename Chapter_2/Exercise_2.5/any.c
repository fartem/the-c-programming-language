#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write the function any(s1,s2), which returns the first location in a string s1
 * where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.
 * (The standard library function strpbrk does the same job but returns a pointer
 * to the location.)
 */

int get_line(char s[], int limit);
int any(char first[], char second[]);

int main(void)
{
    char first[MAX_LENGTH];
    char second[MAX_LENGTH];

    get_line(first, MAX_LENGTH);
    get_line(second, MAX_LENGTH);

    printf("Result: %d\n", any(first, second));
    return 0;
}

int get_line(char s[], int limit)
{
    int i;
    int c;

    for (i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';
    return i;
}

int any(char first[], char second[])
{
    int i, j;
    int match = 1;

    for (i = 0; (first[i] != '\0') && (match);)
    {
        for (j = 0; (first[i] != second[j]) && second[j] != '\0'; i++)
            ;
        if (second[j] == '\0')
        {
            match = 1;
            i++;
        }
        else
        {
            match = 0;
        }
        
    }
    
    if (first[i] == '\0')
        return -1;
    else
        return i;
}
