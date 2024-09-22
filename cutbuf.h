struct string_borders
{
    char** begline;
    char**  endline;
    size_t strings_quantity;
};

string_borders find_borders (char* buf, size_t fsize);
