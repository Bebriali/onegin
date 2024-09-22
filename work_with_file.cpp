#include <stdio.h>
#include "work_with_file.h"

wfile def_file (const char* name, const char* type_stream)
{
    struct wfile cur_file;
    cur_file.name = name;
    cur_file.type_stream = type_stream;

    cur_file.stream = fopen(cur_file.name, cur_file.type_stream);
    if (cur_file.stream == NULL)
    {
        printf("file error [file:origin]\n");
    }

    struct stat st = {};
    if (!stat(cur_file.name, &st))
    {
        printf("error stat\n");
    }
    printf("st.st_size = %ld\n", st.st_size);

    cur_file.fsize = st.st_size;

    return cur_file;
}
