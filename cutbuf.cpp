#include <stdio.h>
#include <stdlib.h>
#include "cutbuf.h"

string_borders find_borders (char* buf, size_t fsize)
{
    struct string_borders cur_borders;
    cur_borders.strings_quantity = 0;
    for(size_t i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            cur_borders.strings_quantity++;
        }
    }

    cur_borders.begline = (char**) calloc(cur_borders.strings_quantity, sizeof(char*));
    if (cur_borders.begline == NULL)
    {
        printf("invalid memory allocation\n");
    }

    cur_borders.endline = (char**) calloc(cur_borders.strings_quantity, sizeof(char*));
    if (cur_borders.endline == NULL)
    {
        printf("invalid memory allocation\n");
    }

    size_t j = 0;
    cur_borders.begline[j] = &buf[j++];
    for (size_t i = 1; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            cur_borders.endline[j]   = &buf[i];
            cur_borders.begline[j++] = &buf[i + 1];
        }
    }

    return cur_borders;
}
