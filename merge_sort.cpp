//#include "TXLib.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int* merge_together(int* a, size_t length_a, int* b, size_t length_b);
int* merge_sort(int* a, size_t length_a);


int* merge_together(int* a, size_t length_a, int* b, size_t length_b)
{
    int* res = (int*) calloc(length_a + length_b, sizeof(int));
    size_t i = 0, j = 0;
    while (i < length_a && j < length_b)
    {
        res[i + j] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
    if (i < length_a)
    {
        while (i < length_a)
        {
            res[i + j] = a[i++];
        }
    }
    if (j < length_b)
    {
        while (j < length_b)
        {
            res[i + j] = b[j++];
        }
    }

    return res;
}

int* merge_sort(int* a, size_t length_a)
{

    if (length_a <= 1)
    {
        return a;
    }
    size_t length_f = length_a / 2;
    size_t length_s = length_a - length_a / 2;

    return merge_together(
        merge_sort(a, length_f), length_f,
        merge_sort(a + length_a / 2, length_s), length_s);
}

int main()
 {
    size_t arr_length = 0;
    scanf("%u", &arr_length);

    int* arr = (int*) calloc(arr_length, sizeof(int));

    for (size_t i = 0; i < arr_length; i++)
    {
        scanf("%d", &arr[i]);
    }

    arr = merge_sort(arr, arr_length);

    for (size_t i = 0; i < arr_length; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
 }
