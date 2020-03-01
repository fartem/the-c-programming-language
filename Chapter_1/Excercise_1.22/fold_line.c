#include <stdio.h>

#define MAXLINESIZE 50
#define MAXFOLDLENGTH 15 

/*
 * Write a program to fold long input lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of input.
 * Make sure your program does something ntelligent with very long lines,
 * and if there are no blanks or tabs before the specified column.
*/

int get_max_line(char line[]);

int main()
{
    int t, length, location, spaceholder;

    char line[MAXLINESIZE];

    while ((length = get_max_line(line)) != 0)
    {
        if (length > MAXFOLDLENGTH)
        {
            t = 0;
            location = 0;

            while (t < length)
            {
                if (line[t] == ' ')
                {
                    spaceholder = t;
                }
                if (location == MAXFOLDLENGTH)
                {
                    line[spaceholder] = '\n';
                    location = 0;
                }
                location++;
                t++;
            }
            
        }
        printf("%s", line);
    }
    return 0;
}

int get_max_line(char line[])
{
    int i, c;

    for (i = 0; i < MAXLINESIZE && ((c = getchar()) != EOF && c != '\n'); i++)
    {
        line[i] = c;
    }
    if (c == '\n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}
