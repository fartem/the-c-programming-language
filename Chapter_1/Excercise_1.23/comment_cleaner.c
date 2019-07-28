#include <stdio.h>

#define MAXLINELENGTH 1000

/*
Write a program to remove all comments from a C program.
Don’t forget to handle quoted strings and character constants properly.
C comments don’t nest.
*/

int get_string(char string[], int limit);
void remove_comments(char string[], char clean_string[]);

int main()
{
    char string[MAXLINELENGTH];
    char clean_string[MAXLINELENGTH];

    get_string(string, MAXLINELENGTH);

    remove_comments(string, clean_string);

    printf("%s", clean_string);

    return 0;
}

int get_string(char string[], int limit)
{
    int c, i = 0;

    while(i < limit - 1 && (c = getchar()) != EOF)
    {
        string[i++] = c;
    }

    if(c == '\n')
    {
        string[i++] = c;
    }

    string[i] = '\0';

    return i;
}

void remove_comments(char string[], char clean_string[])
{
    int in_quote = 0;
    int line_comment = 0;
    int block_comment = 0;

    int i = 0, j = 0;
    while (string[i] != '\0')
    {
        if (in_quote == 0 && string[i] == '"')
        {
            in_quote = 1;
        }
        else if (in_quote == 1 && string[i] == '"')
        {
            in_quote = 0;
        }
        
        if (in_quote == 0)
        {
            if(string[i] == '/' && string[i + 1] == '*' && !line_comment)
            {
                block_comment = 1;
            }

            if(string[i] == '*' && string[i + 1] == '/')
            {
                block_comment = 0;
                i += 2;
            }

            if(string[i] == '/' && string[i] == '/')
            {
                line_comment = 1;
            }

            if(string[i] == '\n')
            {
                line_comment = 0;
            }

            if(line_comment || block_comment)
            {
                ++i;
            }
            else if(!line_comment || !block_comment)
            {
                clean_string[j++] = string[i++];
            }
        }
        else
        {
            clean_string[j++] = string[i++];
        }
    }
    
    clean_string[i] = '\0';
}