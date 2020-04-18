#include <stdio.h>

#define LINE_LENGTH 1000

/*
 * Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 */

int get_line(char s[], int limit);
void str_cat(char *, char *);

int main()
{
    int len;
    char s[LINE_LENGTH], t[LINE_LENGTH];

    get_line(s, LINE_LENGTH);
    printf("s: %s", s);

    get_line(t, LINE_LENGTH);
    printf("t: %s", t);

    str_cat(s, t);
    printf("copy: %s", s);

    return 0;
}

int get_line(char s[], int limit)
{
    int c, i;
    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}

void str_cat(char *s, char *t)
{
    while (*s != '\0')
        s++;
    
    s--;

    while ((*s++ = *t++) != '\0')
        ;
}
