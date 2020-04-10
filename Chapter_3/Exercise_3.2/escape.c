#include <stdio.h>

#define MAX_LENGTH 1000

/*
 * Write a function escape(s,t) that converts characters like newline
 * and tab into visible escape sequences like n and t as it copies the string t to s.
 * Use a switch. Write a function for the other direction as well,
 * converting escape sequences into the real characters.
 */

int get_line(char s[], int limit);
void escape(char s[], char t[]);

int main(void)
{
    char s[MAX_LENGTH];
    char t[MAX_LENGTH];

    getLine(t, MAX_LENGTH);
    escape(s, t);

    printf("%s", s);
    return 0;
}

int get_line(char s[], int limit)
{
    int c, i = 0;
    while (i < limit - 1 && (c = getchar()) != EOF)
        s[i++] = c;

    s[i] = '\0';
}

void escape(char s[], char t[])
{
    int i = 0, j = 0;
    while (t[i] != '\0')
    {
        switch (t[i])
        {
            case '\t':
                s[j] = '\\';
                j++;
                s[j] = 't';
                break;
            case '\n':
                s[j] = '\\';
                j++;
                s[j] = 'n';
                break;
            default:
                s[i] = t[i];
                break;
        }
        i++;
        j++;
    }
    s[j] = '\0';
}
