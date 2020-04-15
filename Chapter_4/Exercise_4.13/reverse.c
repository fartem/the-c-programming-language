#include <stdio.h>
#include <string.h>

/*
 * Write a recursive version of the function reverse(s),
 * which reverses the string s in place.
 */

#define MAX_LENGTH 100

int get_line(char s[], int limit);
void reverse(char s[]);

int main(void)
{
    char s[MAX_LENGTH];
    get_line(s, MAX_LENGTH);
    reverse(s);
    printf("%s\n", s);
    return 0;
}

int get_line(char s[], int limit)
{
    int i, c;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';
    return i;
}

void reverse(char s[])
{
    void reverser(char s[], int i, int length);
    reverser(s, 0, strlen(s));
}

void reverser(char s[], int i, int length)
{
    int j = length - (i + 1);
    if (i < j)
    {
        int c = s[i];
        s[i] = s[j];
        s[j] = c;

        reverser(s, ++i, length);
    }
}
