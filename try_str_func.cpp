#include <stdio.h>
#include <ctype.h>

enum SIZE
{
    HEIGHT = 14,
    WIDTH = 100
};

enum SORT_TYPE
{
    BACK = 0,
    STRAIGHT = 1
};

enum SORT_STATUS
{
    UNSORTED = 0,
    SORTED = 1
};

void put_strings(char text[][WIDTH]);
int compare_strings(const char* first_string, const char* second_string);
void swap_strings(char text[][WIDTH], size_t first_string, size_t second_string);
int compare_back(const char* first_string, const char* second_string);
void sort_strings(char text[][WIDTH], bool sort_type);

int main ()
{


    char text[HEIGHT][WIDTH] = {"With no initention to entertain,",
                                "In love with friendship and regard,",
                                "What i would like is to explain",
                                "A pledge that's worthy or your heart,",
                                "That's worthy of the soul unsmeared,",
                                "Of sacred and completed dream,",
                                "Poetic feelings, loud and clear,",
                                "of lofty thoughts and easy mien;"};

    sort_strings(text, BACK);

    put_strings(text);

    printf("\n");

    sort_strings(text, STRAIGHT);

    put_strings(text);

    return 0;
}


void put_strings (char text[][WIDTH])
{
    for (size_t i = 0; text[i][0] != '\0'; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            printf("%c", text[i][j]);
        }
        printf("\n");
    }
}

int compare_strings (const char* first_string, const char* second_string)
{
    size_t it_first = 0, it_second = 0;
    while(first_string[it_first] != '\0' &&  second_string[it_second] != '\0')
    {
        char cur_first  = first_string [it_first];
        char cur_second = second_string[it_second];

        if (!islower(cur_first) && !isupper(cur_first))
        {
            it_first++;
            continue;
        }
        if (!islower(cur_second) && !isupper(cur_second))
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
        it_first++, it_second++;
    }
    return second_string[it_second] - first_string[it_first];
}

void swap_strings (char text[][WIDTH], size_t first_string, size_t second_string)
{
    for (size_t it = 0; text[first_string][it] != '\0' || text[second_string][it] != '\0'; it++)
    {
        char t = text[first_string][it];
        text[first_string][it] = text[second_string][it];
        text[second_string][it] = t;
    }
}

void sort_strings (char text[][WIDTH], bool sort_type)
{
    bool sort_status = UNSORTED;

    while (!sort_status)
    {
        sort_status = SORTED;

        for (size_t pref = 0; text[pref][0] != '\0'; pref++)
        {
            for (size_t post = pref + 1; text[post][0] != '\0'; post++)
            {
                int cmp_res = ((sort_type == STRAIGHT) ? compare_strings(text[pref], text[post]) : compare_back(text[pref], text[post]));
                if (cmp_res < 0)
                {
                    swap_strings(text, pref, post);
                    sort_status = UNSORTED;
                }
            }
        }
    }
}

int compare_back (const char* first_string, const char* second_string)
{

    size_t first_ending = 0, second_ending = 0;

    while (first_string[first_ending++] != '\0');
    while (second_string[second_ending++] != '\0');

    while(first_ending > 0 &&  second_ending > 0)
    {
        char cur_first  = first_string [first_ending];
        char cur_second = second_string[second_ending];

        if (!islower(cur_first) && !isupper(cur_first))
        {
            first_ending--;
            continue;
        }
        if (!islower(cur_second) && !isupper(cur_second))
        {
            second_ending--;
            continue;
        }

        int difference = tolower(cur_second) - tolower(cur_first);
//        printf("difference = %d, cur_second = %c, cur_first = %c %s/%s\n", difference, cur_second, cur_first, second_string, first_string);
        if (difference)
        {
            return difference;
        }
        first_ending--, second_ending--;
    }
    if (first_ending == second_ending)
    {
        return 0;
    }
    else if(first_ending == 0)
    {
        return 1;
    }

    return -1;
}
