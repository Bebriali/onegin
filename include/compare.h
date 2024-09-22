
enum SORT_TYPE
{
    BACK = 0,
    STRAIGHT = 1,
    ORIGINAL = 2
};

int compare_straight(char** strings, size_t first, size_t second);
void swap_strings(char** strings, size_t first_string, size_t second_string);
int compare_back(char** strings, char** ends, size_t first, size_t second);

void sort_strings(struct string_borders buffer_borders, bool sort_type);
