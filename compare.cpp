#include <stdio.h>
#include <ctype.h>
#include "cutbuf.h"
#include "compare.h"

int compare_straight (char** strings, size_t first, size_t second)
{
//    printf("comparing %s -- %d/ %s -- %d\n", strings[first], first, strings[second], second);
    size_t it_first = 0, it_second = 0;
    while(strings[first][it_first] != '\0' &&  strings[second][it_second] != '\0')
    {
        char cur_first  = strings[first] [it_first];
        char cur_second = strings[second][it_second];

        if (cur_first == '\r' || cur_second == '\r')
        {
            return cur_second - cur_first;
        }

        if (!isalpha(cur_first))
        {
            it_first++;
            continue;
        }
        if (!isalpha(cur_second))
        {
            it_second++;
            continue;
        }

        int difference = tolower(cur_second) - tolower(cur_first);
//        printf("difference = %d, cur_second = %c, cur_first = %c %s/%s\n", difference, cur_second, cur_first, second_string, first_string);
        if (difference)
        {
            return difference;
        }
        it_first++;
        it_second++;
    }
    return 0;
}

int compare_back (char** strings, char** ends, size_t first, size_t second)
{
//    printf("comparing back\n");
//    printf("comparing: %s / %s\n", strings[first], strings[second]);
    size_t first_it = 0, second_it = 0;

    if (strings[first][1] == '.' || strings[second][1] == '.' ||
        strings[first][0] != ' ' || strings[second][0] != ' ')
    {
        return 0;
    }
//    printf("first_it = %d, second_it = %d\n\n", first_it, second_it);
//    size_t first_beg_addr = &strings[first][0];
//    size_t second_beg_addr = &strings[second][0];
    while(first_it < ends[first] - &strings[first][0] && second_it < ends[second] - &strings[second][0])
    {
        char cur_first  = *(ends[first] - first_it);
        char cur_second = *(ends[second] - second_it);
//        printf("\rfirst = %d, second = %d, first_it = %d, second_it = %d",
//                first,      second,      first_it,      second_it);

//        printf("cur_first = %c, cur_second = %c\n", cur_first, cur_second);

        if (!isalpha(cur_first))
        {
            first_it++;
            continue;
        }
        if (!isalpha(cur_second))
        {
            second_it++;
            continue;
        }

//        if (&strings[first][first_it] == *(ends[first] - f_i))
//        {
//            printf("YRA POBEDA SUKA EBATORIYA EBANAYA\n");
//            printf("char stroki = '%c'\n", *(ends[first] - f_i));
//            printf("f_i = %d\n", f_i);
//            printf  ("stroka = %s\n", strings[first]);
//        }

        int difference = tolower(cur_second) - tolower(cur_first);
//        printf("difference = %d, cur_second = %c, cur_first = %c %s/%s\n", difference, cur_second, cur_first, second_string, first_string);
        if (difference)
        {
            return difference;
        }
        first_it++;
        second_it++;
    }


//    printf("equal strings = %s / %s\n", strings[first], strings[second]);

    return *(ends[second] - second_it + 1) - *(ends[first] - second_it);
}

void swap_strings (char** strings, size_t first_string, size_t second_string)
{
    char* t = strings[first_string];
    strings[first_string] = strings[second_string];
    strings[second_string] = t;
}

void sort_strings (string_borders buffer_borders, bool sort_type)
{
    printf("I AM BEGINNING TO SORT SUKA\n");
    printf("strings_quantity kakogoto huya = %d\n", buffer_borders.strings_quantity);
//    for (size_t i = 0; i < buffer_borders.strings_quantity; i++)
//    {
//        printf("\t string[%d] = %s\n", i, buffer_borders.begline[i]);
//    }

//    size_t counter = 0;

    bool arr_sorted = false;

    while (!arr_sorted)
    {
//        printf("\r current counter = %d", counter++);
        arr_sorted = true;

        for (size_t pref = 0; pref < buffer_borders.strings_quantity - 1; pref++)
        {
            for (size_t post = pref + 1; post < buffer_borders.strings_quantity; post++)
            {

//                printf("%d iteration of sec 'for' began\n", post);

                int cmp_res = ((sort_type == STRAIGHT) ?
                    compare_straight (buffer_borders.begline,          pref, post) :
                    compare_back     (buffer_borders.begline, buffer_borders.endline, pref, post));

//                printf("%s %d %s\n", beginnings[pref], cmp_res, beginnings[post]);

                if (cmp_res < 0)
                {

//                    printf("swaping...\n%s / %s\n", beginnings[pref], beginnings[post]);

                    swap_strings(buffer_borders.begline, pref, post);

//                    printf("swaped:\n%s / %s\n", beginnings[pref], beginnings[post]);

                    arr_sorted = false;
                }

//                printf("%d iteration of sec 'for' ended\n", post);
//                printf("post < strings_quantity ? : %d\n", post < strings_quantity);

            }
            printf("\rpref = %d", pref);
        }
        printf("LOX SUKA");
    }
    printf("\n");
    printf("SORTING COMPLETED\n");
//    printf("\n");
}
