#include <stdio.h>

#define IN 1
#define OUT 0

/*
How would you test the word count program?
What kinds of input are most lineskely to uncover bugs if there are any?

Test with empty strings and large input
*/

int main()
{
    int words = 0;
    int lines = 0;
    int chars = 0;

    int state = OUT;

    char c;

    while ((c = getchar()) != EOF)
    {
        chars++;
        if (c == '\n')
        {
            lines++;
        }
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            words++;
        }
    }

    printf("Words: %d\nLines: %d\nSymbols: %d", words, lines, chars);
    return 0;
}