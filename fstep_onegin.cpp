#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include "put_strings.h"

int main ()
{
    const char* filename = "text.txt";
    const char* result_filename = "onegin_sorted.txt";

    printf("opening result file...\n");
    FILE * result = fopen(result_filename, "wb");
    if (result == NULL)
    {
        printf("error write result\n");
        return FILE_ERROR;
    } printf("result file opened\n");
    fputs("original and sorted straight and back onegin\n", result);
//    printf("current result_file position = %ld\n", ftell(result));

    printf("opening original file...\n");
    FILE * poem = fopen(filename, "rb");
    if (poem == NULL)
    {
        printf("file error [file:origin]\n");
        return FILE_ERROR;
    } printf("original file opened\n");

    struct stat st = {};
    if (!stat(filename, &st))
    {
        printf("error stat\n");
    }
    printf("st.st_size = %ld\n", st.st_size);

    char* buffer = (char*) calloc(st.st_size + 1, sizeof(char));
    if (buffer == NULL)
    {
        printf("invalid memory allocation\n");
        return ALLOC_ERROR;
    }

    size_t file_size = fread(buffer, sizeof(char), st.st_size + 1, poem);

    printf("file_size = %d\n", file_size);

    size_t strings_quantity = 0;

    for(size_t i = 0; i < file_size; i++)
    {
        if (buffer[i] == '\n')
        {
            strings_quantity++;
        }
    }

    printf("strings_quantity = %d\n", strings_quantity);

    char** beginnings = (char**) calloc(strings_quantity, sizeof(char*));
    if (beginnings == NULL)
    {
        printf("invalid memory allocation\n");
        return ALLOC_ERROR;
    }

    size_t j = 0;
    beginnings[j++] = &buffer[0];
    for (size_t i = 1; i < file_size; i++)
    {
        if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
        }
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            beginnings[j++] = &buffer[i + 1];
        }
    }

//    for (int i = 0; i < strings_quantity; i++)
//    {
//        printf("endings[%d][0] = %d\n", i, endings[i]);
//        printf("endings[%d][-2] = '%c'\n", i, *((char*)&endings[i]));
//    }


    /**/printf("before first put_strings\n");
    /**/printf("current result_file position = %ld\n", ftell(result));
    fputs("original version\n"
          "-----------\n", result);
//    /**/printf("current result_file position = %d\n", ftell(result));

    put_strings (beginnings, strings_quantity, result);
    /**/printf("first put_strings completed\n");

    sort_strings(beginnings, STRAIGHT, strings_quantity);
    /**/printf("sort_straight completed\n");

    fputs("sorted straight version\n"
          "------------\n", result);
//    /**/printf("current result_file position = %d\n", ftell(result));

    put_strings (beginnings, strings_quantity, result);

    printf("sorting_strings back...\n");
    sort_strings(beginnings, BACK, strings_quantity);
    /**/printf("sort_backwards completed\n");

    fputs("sorted back version\n"
          "------------\n", result);
//    /**/printf("current result_file position = %ld\n", ftell(result));

    put_strings (beginnings, strings_quantity, result);
    /**/printf("sec put_strings completed\n");

    fclose(result);
    fclose(poem);

    free(buffer);
    buffer = NULL;

    return 0;
}
