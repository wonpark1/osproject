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

void print_matches(const char* line, const char* word, int ignore_case) {
    const char* ptr = line;
    size_t len = strlen(word);
    while (*ptr) {
        if (ignore_case) {
            if (strncasecmp(ptr, word, len) == 0) {
                printf("%.*s\n", (int)len, ptr);
                ptr += len;
                continue;
            }
        }
        else {
            if (strncmp(ptr, word, len) == 0) {
                printf("%.*s\n", (int)len, ptr);
                ptr += len;
                continue;
            }
        }
        ptr++;
    }
}

void command_grep(int argc, char** argv) {
    int show_line_number = 0;
    int ignore_case = 0;
    int invert_match = 0;
    int only_matching = 0;
    const char* word = NULL;
    const char* filename = NULL;

    // �ɼ� �Ľ�
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {//������ flag ó���� ���� ������� �Է°���
                if (argv[i][j] == 'n') show_line_number = 1;
                else if (argv[i][j] == 'i') ignore_case = 1;
                else if (argv[i][j] == 'v') invert_match = 1;
                else if (argv[i][j] == 'o') only_matching = 1;
                else {
                    printf(" �� �� ���� �ɼ��Դϴ�: -%c\n", argv[i][j]);
                    return;
                }
            }
        }
        else if (!word) {
            word = argv[i];
        }
        else if (!filename) {
            filename = argv[i];
        }
        else {
            printf(" ���ڰ� �ʹ� �����ϴ�.\n");
            printf("����: grep [-n] [-i] [-v] [-o] <�˻���> <���ϸ�>\n");
            return;
        }
    }

    if (!word || !filename) {
        printf(" �˻��� �Ǵ� ���ϸ��� �������ϴ�.\n");
        printf("����: grep [-n] [-i] [-v] [-o] <�˻���> <���ϸ�>\n");
        return;
    }

    //-v�� -o�� �Բ� ����� �� ����
    if (invert_match && only_matching) {
        printf(" -o(��ġ �ܾ ���) �ɼ��� -v(���� �˻�) �ɼǰ� �Բ� ����� �� �����ϴ�.\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf(" ������ �� �� �����ϴ�: %s\n", filename);
        return;
    }

    char line[1024];
    int line_num = 1;
    while (fgets(line, sizeof(line), file)) {
        int match = ignore_case
            ? strcasestr_custom(line, word)
            : strstr(line, word) != NULL;

        if (invert_match)
            match = !match;

        if (match) {
            if (only_matching) {
                print_matches(line, word, ignore_case);
            }
            else {
                if (show_line_number)
                    printf("%d: %s", line_num, line);
                else
                    printf("%s", line);
            }
        }

        line_num++;
    }

    fclose(file);
}
