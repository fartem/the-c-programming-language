#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write the function strindex(s,t) which returns the position of the rightmost occurrence
 * of t in s, or -1 if there is none.
 */

int stringindex(char s[], char t[]);

int main()
{
    char line[] = "Test string for find pattern";
    char pattern[] = "for";

    int result = stringindex(line, pattern);

    printf("String \"%s\" contains \"%s\" at position: %d\n", line, pattern, result);
    return 0;
}

int stringindex(char s[], char t[])
{
    int i;
    int j;
    int k;
    int result = -1;

    for (i = 0; i < s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
        {
            result = i;
        }
    }
    return result;
}
