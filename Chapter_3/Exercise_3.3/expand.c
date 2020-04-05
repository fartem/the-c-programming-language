#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1
 * into the equivalent complete list abc…xyz in s2. Allow for letters of either case and digits,
 * and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading
 * or trailing -is taken literally.
 */

int getLine(char s[], int limit);
void expand(char first[], char second[]);

int main()
{
    char first[MAX_LENGTH];
    char second[MAX_LENGTH];

    getLine(first, MAX_LENGTH);
    expand(first, second);

    printf("Expanded string: %s", second);
    return 0;
}

int getLine(char s[], int limit)
{
    int c;
    int i;
    
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
}

void expand(char first[], char second[])
{
    int i = 0;
    int j = 0;
    int c;

    while ((c = first[i++]) != '\0')
    {
        if (first[i] == '-' && first[i + 1] >= c)
        {
            i++;
            while (c < first[i])
            {
                second[j++] = c++;
            }
        }
        else
        {
            second[j++] = c;
        }
    }
    second[j] = '\0';
}
