#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write an alternative version of squeeze(s1,s2) that deletes each character
 * in s1 that matches any character in the string s2.
 */

int getLine(char s[], int limit);
int squeeze(char first[], char second[]);

int main()
{
    char first[MAX_LENGTH];
    char second[MAX_LENGTH];

    printf("First: ");
    getLine(first, MAX_LENGTH);

    printf("Second: ");
    getLine(second, MAX_LENGTH);

    squeeze(first, second);

    printf("Result: %s\n", first);
    return 0;
}

int getLine(char s[], int limit)
{
    int i;
    int c;

    for (i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

int squeeze(char first[], char second[])
{
    int j;
    int k = 0;
    for (int i = 0; first[i] != '\0'; i++)
    {
        for (j = 0; (first[i] != second[j]) && second[j] != '\0'; j++)
            ;
        if (second[j] == '\0')
        {
            first[k++] = first[i];
        }
    }
    first[k] = '\0';
}
