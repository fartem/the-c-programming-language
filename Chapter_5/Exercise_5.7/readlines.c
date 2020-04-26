#include <stdio.h>
#include <string.h>

#define MAX_LINES 5000

/*
 * Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage.
 * How much faster is the program?
 */

char *lineptr[MAX_LINES];
char linestor[MAX_LINES];

int read_lines(char *[], char *, int);
void write_lines(char *[], int);

void q_sort(char *[], int, int);

int main(void)
{
    int lines;
    if ((lines = read_lines(lineptr, linestor, MAX_LINES)) >= 0)
    {
        q_sort(lineptr, 0, lines - 1);
        write_lines(lineptr, lines);
        return 0;
    }
    else
    {
        printf("error: input too big to sort!\n");
        return 1;
    }
}

#define MAX_LENGTH 1000
#define MAX_STOR 5000

int get_line(char *, int);
char *alloc(int);

int read_lines(char *lineptr[], char *linestor, int limit)
{
    int len;
    int lines = 0;
    char line[MAX_LENGTH];
    char *p = linestor;
    char *linestop = linestor + MAX_STOR;

    while ((len = get_line(line, MAX_LENGTH)) > 0)
    {
        if (lines > limit || p + len > linestop)
        {
            return -1;
        }
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[lines++] = p;
            p += len;
        }
    }
    return lines;
}

void write_lines(char *lineptr[], int limit)
{
    for (int i = 0; i < limit; i++)
        printf("%s\n", lineptr[i]);
}

void q_sort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    
    swap(v, left, last);
    q_sort(v, left, last - 1);
    q_sort(v, last + 1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define ALLOCATE_SIZE 10000

static char alloc_buffer[ALLOCATE_SIZE];
static char *allocp = alloc_buffer;

char *alloc(int n)
{
    if (alloc_buffer + ALLOCATE_SIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    return 0;
}

int get_line(char *s, int limit)
{
    int c;
    char *t = s;

    while (--limit > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return s - t;
}
