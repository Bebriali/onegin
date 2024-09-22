#include <sys/stat.h>

struct wfile
{
    const char* name;
    const char* type_stream;
    FILE* stream;
    int fsize;
};

wfile def_file (const char* name, const char* type_stream);
