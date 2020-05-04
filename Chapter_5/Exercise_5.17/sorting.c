#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * Add a field-searching capability, so sorting may bee done
 * on fields within lines, each field sorted according
 * to an independent set of options.
 * (The index for this book was sorted with -df
 * for the index category and -n for the page numbers.)
 */

#define NUMERIC 1
#define DECR 2
#define FOLD 4
#define MDIR 8
#define LINES 100

int charcmp(char *, char *);
void error(char *);
int numcmp(char *, char *);
void readargs(int, char *[]);
int readlines(char *[], int);
void q_sort(void *[], int, int, int (*comp) (void *, void*));
void writelines(char *[], int, int);

int option = 0;

int pos1 = 0;
int pos2 = 0;

int main(int argc, char *argv[])
{
    char *lineptr[LINES];
    int nlines;
    int rc = 0;

    readargs(argc, argv);

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
        error("error: input too big to sort!");
        rc = -1;
    }
    return rc;
}

void readargs(int argc, char *argv[])
{
    int c;
    while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+')
    {
        if (c == '-' && !isdigit(*(argv[0] + 1)))
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
                        error("error: illegal option!");
                        break;
                }
            }
        }
        else if (c == '-')
        {
            pos2 = atoi(argv[0] + 1);
        }
        else
        {
            error("Usage: sort [-dfnr] [+pos1] [-pos2]");
        }
    }

    if (argc || pos1 > pos2)
        error("Usage: sort [-dfnr] [+pos1] [-pos2]");
}

#include <math.h>
#include <ctype.h>
#include <string.h>

#define STRING_LENGTH 100

void substr(char *, char *);

int numcmp(char *s1, char *s2)
{
    double v1, v2;
    char str[STRING_LENGTH];

    substr(s1, str);
    v1 = atof(str);

    substr(s2, str);
    v2 = atof(str);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int charcmp(char *s, char *t)
{
    char a, b;
    int i, j, endpos;

    extern int option, pos1, pos2;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & MDIR) ? 1 : 0;

    i = j = pos1;

    if (pos2 > 0)
        endpos = pos2;
    else if ((endpos = strlen(s)) > strlen(t))
        endpos = strlen(t);
    
    do
    {
        if (dir)
        {
            while (i < endpos && !isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
                i++;
            
            while (j < endpos && !isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
                j++;
        }
        if (i < endpos && j < endpos)
        {
            a = fold ? tolower(s[i]) : s[i];
            i++;

            b = fold ? tolower(t[j]) : t[j];
            j++;

            if (a == b && a == '\0')
                return 0;
        }
    } while (a == b && i < endpos && j < endpos);

    return a - b;
}

void substr(char *s, char *t)
{
    int i, j, len;
    extern int pos1, pos2;

    len = strlen(s);

    if (pos2 > 0 && len > pos2)
        len = pos2;
    else if (pos2 > 0 && len < pos2)
        error("error: string too short!");
    
    for (j = 0, i = pos1; i < len; i++, j++)
        t[j] = t[i];

    t[j] = '\0';
}

void error(char *s)
{
    printf("%s\n", s);
    exit(1);
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
