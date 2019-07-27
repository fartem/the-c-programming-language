#include <stdio.h>

#define VERSION 9

void print_with_new_line(char *__args, ...);

int main()
{
    print_with_new_line("Version: %d", VERSION);
    return 0;
}

void print_with_new_line(char *__args, ...)
{
    printf(__args, '\n');
}