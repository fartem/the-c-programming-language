#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000

/*
 * Write versions of the library functions strncpy, strncat,
 * and strncmp, which operate on at most the first n characters
 * of their argument strings.
 */

void str_copy(char *, char *, int);
void str_cat(char *, char *, char *, int);
int str_cmp(char *, char *, int);

int main()
{
    char dest[] = "ABCD";
    char source[] = "EFG";
    
    str_copy(dest, source, 1);
    printf("str_copy: %s\n", dest);

    char s[] = "ABC";
    char t[] = "DEF";
    char *d = (char *) malloc(sizeof(char) * (strlen(s) + + 4 + 1));

    str_cat(s, t, d, 3);
    printf("str_cat: %s\n", d);

    free(d);

    int cmp = str_cmp(s, t, 3);
    printf("str_cmp: %d\n", cmp);

    return 0;
}

void str_copy(char *dest, char *source, int n)
{
    while (*source && n-- > 0)
        *dest++ = *source++;
    
    int extra = strlen(dest) - n;

    while (extra-- > 0)
        *dest++;

    *dest = '\0';
}

void str_cat(char *s, char *t, char *dest, int n)
{
    while (*s)
        *dest++ = *s++;
    
    while (n-- > 0)
        *dest++ = *t++;
    
    *dest = '\0';
}

int str_cmp(char *s, char *t, int n)
{
    for (; *s++ == *t++;)
        if (*s == '\0' || --n < 0)
            return 0;
    
    return *s - *t;
}
