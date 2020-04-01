#include <stdio.h>

#define MAX_LENGTH 1000

#define TRUE 1
#define FALSE 0

int getLine(char s[], int limit);
int htoi(char s[]);

int main()
{
    char line[MAX_LENGTH];
    int value;

    getLine(line, MAX_LENGTH);
    value = htoi(line);

    printf("Casted value (original: %s): %d\n", line, value);
    return 0;
}

int getLine(char s[], int limit)
{
    int i;
    int c;

    for (i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

int htoi(char s[])
{
    int hexDigit;
    int i = 0;
    int inHex = TRUE;
    int n = 0;

    if (s[i] == '0')
    {
        i++;
        if (s[i] == 'x' || s[i] == 'X')
        {
            i++;
        }
    }
    for (; inHex == TRUE; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            hexDigit = s[i] - '0';
        }
        else if (s[i] >= 'a' && s[i] <= 'f')
        {
            hexDigit = s[i] - 'a' + 10;
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            hexDigit = s[i] - 'A' + 10;
        }
        else
        {
            inHex = FALSE;
        }

        if (inHex == TRUE)
        {
            n = 16 * n + hexDigit;
        }
    }
    return n;
}
