#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/grep.h"

int strcasestr_custom(const char* haystack, const char* needle) {
    char lower_hay[1024], lower_need[256];
    int i;
    for (i = 0; haystack[i] && i < sizeof(lower_hay) - 1; i++)
        lower_hay[i] = tolower(haystack[i]);
    lower_hay[i] = '\0';

    for (i = 0; needle[i] && i < sizeof(lower_need) - 1; i++)
        lower_need[i] = tolower(needle[i]);
    lower_need[i] = '\0';

    return strstr(lower_hay, lower_need) != NULL;
}

void command_grep(int argc, char** argv) {
    int show_line_number = 0;
    int ignore_case = 0;
    const char* word = NULL;
    const char* filename = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) show_line_number = 1;
        else if (strcmp(argv[i], "-i") == 0) ignore_case = 1;
        else if (strcmp(argv[i], "-ni") == 0 || strcmp(argv[i], "-in") == 0) {
            show_line_number = 1;
            ignore_case = 1;
        }
        else if (!word) word = argv[i];
        else if (!filename) filename = argv[i];
    }

    if (!word || !filename) {
        printf("Usage: grep [-n] [-i] <word> <filename>\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file: %s\n", filename);
        return;
    }

    char line[1024];
    int line_num = 1;
    while (fgets(line, sizeof(line), file)) {
        int match = 0;
        if (ignore_case)
            match = strcasestr_custom(line, word);
        else
            match = strstr(line, word) != NULL;

        if (match) {
            if (show_line_number)
                printf("%d: %s", line_num, line);
            else
                printf("%s", line);
        }
        line_num++;
    }

    fclose(file);
}
