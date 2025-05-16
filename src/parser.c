
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

