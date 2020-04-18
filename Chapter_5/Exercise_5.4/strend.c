#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 1000

/*
 * Write the function strend(s,t), which returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise.
 */

int get_line(char s[], int limit);
int str_end(char *, char *);
int str_len(char *);

int main()
{
    char s[LINE_LENGTH], t[LINE_LENGTH];
    int contains;

    get_line(s, LINE_LENGTH);
    get_line(t, LINE_LENGTH);

    contains = str_end(s, t);
    printf("Contains: %d\n", contains);

    return 0;
}

int get_line(char s[], int limit)
{
    int i, c;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;
    
    s[i] == '\0';
    return i;
}

int str_end(char *s, char *t)
{
    int len = strlen(t);
    while (*s != '\0')
        s++;
    
    s--;

    while (*t != '\0')
        t++;
    
    t--;

    for (; len > 0 && (*t-- == *s--); len--)
        ;

    return (len == 0) ? 1 : 0;
}
