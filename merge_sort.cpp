#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "compare.h"
#include "merge_sort.h"

char** merge_together(char** a, size_t length_a, char** b, size_t length_b, bool sort_type)
{
    char** res = (char**) calloc(length_a + length_b, sizeof(int));
    size_t i = 0, j = 0;
    while (i < length_a && j < length_b)
    {
//        printf(" a[%d] = %s\n", i, a[i]);
//        printf(" b[%d] = %s\n", j, b[j]);
        int cmp_str = compare_straight (a[i], b[j]);
        if (cmp_str < 0)
        {
//            printf("we are taking b[%d]\n", j);
            res[i + j] = b[j++];
//            printf("res[%d] = %s\n\n", j + i - 1, res[i + j - 1]);
        }
        else
        {
//            printf("we are taking a[%d]\n", i);
            res[i + j] = a[i++];
//            printf("res[%d] = %s\n\n", i + j - 1, res[i + j - 1]);
        }
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
//
//    printf("\n" "merge_result:\n");
//    for (size_t r = 0; r < length_a + length_b; r++)
//    {
//        printf("res[%d] = %s\n", r, res[r]);
//    }


    return res;
}

char** merge_sort(char** a, size_t length_a, bool sort_type)
{

    if (length_a <= 1)
    {
        return a;
    }
    size_t length_f = length_a / 2;
    size_t length_s = length_a - length_a / 2;

    return merge_together(
        merge_sort(a, length_f, sort_type),                length_f,
        merge_sort(a + length_a / 2, length_s, sort_type), length_s,
        sort_type);
    return 0;
}
