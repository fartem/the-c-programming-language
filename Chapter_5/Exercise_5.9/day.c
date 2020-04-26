#include <stdio.h>

/*
 * Rewrite the routines day_of_year and month_day
 * with pointers instead of indexing.
 */

static char day_tab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

void day_of_year(int, int, int*);
void month_day(int, int, int*, int*);

int main(void)
{
    int day;
    day_of_year(1985, 3, &day);
    printf("Day: %d\n", day);

    int month, date;
    month_day(1977, 5, &month, &date);
    printf("%d, %d\n", month, date);

    return 0;
}

void day_of_year(int year, int month, int *day)
{
    
    *day = 0;
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    for (int i = 1; i < month; i++)
        *day += day_tab[leap][i];
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    int i;
    for (i = 1; i <= 12 && yearday > day_tab[leap][i]; i++)
        yearday -= day_tab[leap][i];

    *pmonth = i;
    *pday = yearday;
}
