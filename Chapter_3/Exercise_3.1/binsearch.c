#include <stdio.h>

/*
 * Our binary search makes two tests inside the loop,
 * when one would suffice (at the price of more tests outside.)
 * Write a version with only one test inside the loop
 * and measure the difference in runtime.
 */

int binSearch(int x, int arr[], int n);

int main()
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    printf("%d", binSearch(1, arr, 10));
    return 0;
}

int binSearch(int x, int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;

    while (low < high && x != arr[mid])
    {
        if (x > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            low = high - 1;
        }
    }
    if (x == arr[mid])
    {
        return mid;
    }
    else
    {
        return -1;
    }
}
