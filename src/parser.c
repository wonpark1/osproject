
#include "include/command.h"
#include <string.h>
#include <stdlib.h>

void ParseAndExecute(char* input) {
    char* argv[10];
    int argc = 0;
    char* token = strtok(input, " ");

    while (token != NULL && argc < 10) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return;

    if (strcmp(argv[0], "ls") == 0) {
        command_ls(argc, argv);
    } else if (strcmp(argv[0], "mkdir") == 0) {
        command_mkdir(argc, argv);
    } else {
        printf("🔍 Unknown command: %s\n", argv[0]);
    }
}

// 호출 전에 명령어를 alias로 치환
void ReplaceAlias(AliasTable* table, char* input) {
    char original[100];
    strcpy(original, input);

    char* token = strtok(original, " ");
    if (!token) return;

    for (int i = 0; i < table->count; i++) {
        if (strcmp(token, table->list[i].name) == 0) {
            // 별칭을 실제 명령어로 바꿈
            char replaced[200];
            snprintf(replaced, sizeof(replaced), "%s %s", table->list[i].command, input + strlen(token));
            strcpy(input, replaced);
            return;
        }
    }
}

void ParseAndExecute(DTree* tree, Stack* stack, UList* user, AliasTable* aliases, char* input) {
    ReplaceAlias(aliases, input);  // alias 치환 먼저

    char* argv[10];
    int argc = 0;
    char* token = strtok(input, " ");
    while (token && argc < 10) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc == 0) return;

    if (strcmp(argv[0], "alias") == 0) {
        command_alias(aliases, argc, argv);
    } else if (strcmp(argv[0], "cat") == 0) {
        command_cat(tree, argv[1]);
    }
}


