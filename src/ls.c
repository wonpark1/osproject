#include <stdio.h>
#include <string.h>
#include "../include/ls.h"

void print_permissions(int permission[9]) {
    const char* rwx = "rwx";
    for (int i = 0; i < 9; i++) {
        printf("%c", permission[i] ? rwx[i % 3] : '-');
    }
}

void print_long_format(TNode* node) {
    printf("%c", node->type);
    print_permissions(node->permission);
    printf(" %d %d %5d %02d-%02d %02d:%02d %s\n",
        node->UID, node->GID, node->SIZE,
        node->month, node->day, node->hour, node->minute,
        node->name);
}

void print_short_format(TNode* node) {
    if (strlen(node->name) < 8)
        printf("%s\t\t", node->name);
    else
        printf("%s\t", node->name);
}

void command_ls(DTree* tree, int argc, char** argv) {
    int show_all = 0, long_format = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) show_all = 1;
        else if (strcmp(argv[i], "-l") == 0) long_format = 1;
        else if (strcmp(argv[i], "-al") == 0 || strcmp(argv[i], "-la") == 0)
            show_all = long_format = 1;
    }

    int count = 0;

    if (show_all) {
        // "." 출력
        TNode* current = tree->current;
        if (long_format) print_long_format(current);
        else print_short_format(current);
        count++;

        // ".." 출력
        TNode* parent = current->Parent;
        if (parent) {
            if (long_format) print_long_format(parent);
            else print_short_format(parent);
            count++;
        }

        if (!long_format && count % 5 == 0) printf("\n");
    }

    TNode* node = tree->current->left;
    while (node) {
        if (!show_all && node->name[0] == '.') {
            node = node->right;
            continue;
        }

        if (long_format) print_long_format(node);
        else {
            print_short_format(node);
            if (++count % 5 == 0) printf("\n");
        }

        node = node->right;
    }

    if (!long_format && count % 5 != 0) printf("\n");
}
