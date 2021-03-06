#include <stdio.h>

#define MAX_LENGTH 1000

#define TRUE 1
#define FALSE 0

/*
 * Write a function htoi(s), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f,and A through F.
 */

int get_line(char s[], int limit);
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

int get_line(char s[], int limit)
{
    int i, c;
    for (i = 0; i < limit && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';
    return i;
}

int htoi(char s[])
{
    int hex_digit;
    int i = 0;
    int in_hex = TRUE;
    int n = 0;

    if (s[i] == '0')
    {
        i++;
        if (s[i] == 'x' || s[i] == 'X')
            i++;
    }
    for (; in_hex == TRUE; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            hex_digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            hex_digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            hex_digit = s[i] - 'A' + 10;
        else
            inHex = FALSE;

        if (inHex == TRUE)
            n = 16 * n + hex_digit;
    }
    return n;
}
