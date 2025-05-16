#include "include/command.h"
#include "include/parser.h"
#include <stdio.h>
#include <string.h>

int main() {
    char cmd[100];

    printf("🌿 Welcome to the Mini OS Shell 🌿\n");
    printf("Type your command below (type 'exit' to quit):\n");

    while (1) {
        printf("myos$ ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0) break;

        ParseAndExecute(cmd);
    }

    return 0;
}

