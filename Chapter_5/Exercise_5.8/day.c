#include <stdio.h>

/*
 * There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */

static char day_tab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

int day_of_year(int, int, int);
void month_day(int, int);

int main(void)
{
    int day = day_of_year(1999, 1, 1);
    printf("Day: %d\n", day);
    month_day(1981, 3);

    return 0;
}

int day_of_year(int year, int month, int day)
{
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    for (int i = 1; i < month; i++)
        day += day_tab[leap][i];

    return day;
}

void month_day(int year, int yearday)
{
    int i;
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    for (i = 1; yearday > day_tab[leap][i]; i++)
        yearday -= day_tab[leap][i];
    
    printf("Month: %d, Day: %d\n", i, yearday);
}
