#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "put_strings.h"
#include "compare.h"
#include "work_with_file.h"
#include "cutbuf.h"
#include "merge_sort.h"

void make_text (wfile result_file, string_borders buffer_borders, bool sort_type);

const char* choose_vers (const int sort_type);

int main ()
{
    const char* origin_filename = "onegin.txt";
    const char* or_type_stream = "r+b";
    const char* result_filename = "onegin_sorted.txt";
    const char* res_type_stream = "wb";

    struct wfile result_file = def_file(result_filename, res_type_stream);
    struct wfile origin_file = def_file(origin_filename, or_type_stream);

    char* buffer = (char*) calloc(origin_file.fsize + 1, sizeof(char));
    if (buffer == NULL)
    {
        printf("invalid memory allocation\n");
        return ALLOC_ERROR;
    }

    size_t file_size = fread(buffer, sizeof(char), origin_file.fsize, origin_file.stream);

    printf("file_size = %d\n", file_size);

    struct string_borders buffer_borders = find_borders(buffer, origin_file.fsize);
    fseek(origin_file.stream, 0, SEEK_SET);
    put_strings (buffer_borders.begline, buffer_borders.strings_quantity, origin_file.stream);
    fseek(origin_file.stream, 0, SEEK_SET);
    file_size = fread(buffer, sizeof(char), origin_file.fsize, origin_file.stream);
    buffer_borders = find_borders(buffer, origin_file.fsize);
    printf("file_size = %d\n", file_size);

//    make_text(result_file, buffer_borders, ORIGINAL);
    make_text(result_file, buffer_borders, STRAIGHT);
//    make_text(result_file, buffer_borders, BACK);

    fclose(result_file.stream);
    fclose(origin_file.stream);

    free(buffer);
    buffer = NULL;

    return 0;
}

void make_text (wfile result_file, string_borders buffer_borders, bool sort_type)
{
    if (sort_type != ORIGINAL)
    {
        buffer_borders.begline = merge_sort(buffer_borders.begline, buffer_borders.strings_quantity, sort_type);
    }
//    for (size_t i = 0; i < buffer_borders.strings_quantity; i++)
//    {
//        printf("begline[%d] = %s\n", i, buffer_borders.begline[i]);
//    }

    const char* version = choose_vers(sort_type);

    fputs(version, result_file.stream);
    fputs(" version\n"
          "-----------\n", result_file.stream);

    put_strings (buffer_borders.begline, buffer_borders.strings_quantity, result_file.stream);
}

const char* choose_vers (const int sort_type)
{
    switch (sort_type)
    {
        case BACK:
            return "sorted back";
        case STRAIGHT:
            return "sorted straight";
        case ORIGINAL:
            return "original";
        default:
            printf("error: wrong sort_type\n");
            break;
    }
    return 0;
}
