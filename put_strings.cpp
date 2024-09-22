#include<stdio.h>
#include <ctype.h>
#include "put_strings.h"

void put_strings (char** strings, size_t strings_quantity, FILE * filename)
{
    printf("begin put_strings\n");
    printf("strings_quantity = %d\n", strings_quantity);
    for (size_t i = 0; i < strings_quantity; i++)
    {
//        printf("string [%d] = %s\n", i, strings[i]);
        if (strings[i][0] != '\0' && (strings[i][0] == ' ' || strings[i][0] == '\t'))
        {
            printf("strings[%d] = %s\n", i, strings[i]);
            fputs(strings[i], filename);
//            printf("LOSHARA CHUSHKA EBANAYA\n");
            fputs("\n", filename);
        }

//        printf("current result_file position = %d\n", ftell(filename));
    }
    printf("all strings are written in file\n");

}
