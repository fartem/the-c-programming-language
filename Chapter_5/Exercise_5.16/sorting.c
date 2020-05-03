#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * Add the -d (directory order) option, which makes comparisons only
 * on letters, numbers and blanks. Make sure it works in conjunction with -f.
 */

 #define NUMERIC 1
 #define DECR 2
 #define FOLD 4
 #define MDIR 8
 #define LINES 100

int charcmp(char *, char *, int);
int numcmp(char *, char *);
int readlines(char *[], int);
void q_sort(void *[], int, int, int (*comp) (void *, void *));
void writelines(char *[], int, int);

int main(int argc, char *argv[])
{
    int option = 0;
    char *lineptr[LINES];
    int nlines;
    int c, rc = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while (c = *++argv[0])
        {
            switch (c)
            {
                case 'd':
                    option |= MDIR;
                    break;
                case 'f':
                    option |= FOLD;
                    break;
                case 'n':
                    option |= NUMERIC;
                    break;
                case 'r':
                    option |= DECR;
                    break;
                default:
                    printf("sort: Illegal option %c\n", c);
                    argc = 1;
                    rc = -1;
                    break;
            }
        }
    }
    if (argc)
    {
        printf("usage: sort [-nr]\n");
        rc = -1;
    }
    else
    {
        if ((nlines = readlines(lineptr, LINES)) > 0)
        {
            if (option & NUMERIC)
                q_sort((void **) lineptr, 0, nlines - 1, (int (*) (void *, void *)) numcmp);
            else
                q_sort((void **) lineptr, 0, nlines - 1, (int (*) (void *, void *)) charcmp);
            
            writelines(lineptr, nlines, option & DECR);
        }
        else
        {
            printf("error: input too big to sort!\n");
            rc = -1;
        }
    }
    return rc;
}

void writelines(char *lineptrp[], int nlines, int option)
{
    if (option)
    {
        for (int i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptrp[i]);
    }
    else
    {
        for (int i = 0; i < nlines; i++)
            printf("%s\n", lineptrp[i]);
    }
}

int charcmp(char *s, char *t, int option)
{
    char a, b;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & MDIR) ? 1 : 0;

    do
    {
        if (dir)
        {
            while (!isalnum(*s) && *s != ' ' && *s != '\0')
                s++;
            while (!isalnum(*t) && *t != ' ' && *t != '\0')
                t++;
        }

        a = fold ? tolower(*s) : *s;
        s++;

        b = fold ? tolower(*t) : *t;
        t++;

        if (a == b && a == '\0')
            return 0;
    } while (a == b);
    return a - b;
}

#include <stdlib.h>

int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

#define LINE_LENGTH 1000

int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int limit)
{
    char len, nlines;
    char *p, line[LINE_LENGTH];
    nlines = 0;
    
    while ((len = get_line(line, LINE_LENGTH)) > 1)
    {
        if (nlines >= limit || (p = alloc(len)) == NULL)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

#define ALLOC_SIZE 1000

static char allocbuf[ALLOC_SIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    void afree(char *);

    if (allocbuf + ALLOC_SIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
    {
        return 0;
    }
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOC_SIZE)
        allocp = p;
}

void q_sort(void *v[], int l, int r, int (*comp) (void *, void *))
{
    int i, last;
    void swap(void *[], int, int);

    if (l >= r)
        return;

    swap(v, l, (l + r) / 2);

    last = l;

    for (i = l + 1; i <= r; i++)
    {
        if ((*comp) (v[i], v[l]) < 0)
            swap(v, ++last, i);
    }

    swap(v, l, last);

    q_sort(v, l, last - 1, comp);
    q_sort(v, last + 1, r, comp);
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
