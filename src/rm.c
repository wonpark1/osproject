#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/osproject.h"
#include "../include/command.h"

extern DTree* tree;

void delete_node(TNode* parent, const char* name, int recursive, int force, int verbose) {
    TNode* prev = NULL;
    TNode* curr = parent->left;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (curr->type == 'd' && !recursive) {
                if (!force)
                    printf("rm: 디렉토리 '%s'를 지우려면 -r 옵션이 필요합니다.\n", name);
                return;
            }

            if (curr->type == 'd' && recursive) {
                while (curr->left)
                    delete_node(curr, curr->left->name, recursive, force, verbose);
            }

            if (verbose)
                printf("삭제됨: %s\n", curr->name);

            if (prev)
                prev->right = curr->right;
            else
                parent->left = curr->right;

            free(curr);
            return;
        }

        prev = curr;
        curr = curr->right;
    }

    if (!force)
        printf("rm: '%s': 그런 파일이나 디렉터리가 없습니다.\n", name);
}

void command_rm(int argc, char** argv) {
    int recursive = 0, force = 0, verbose = 0;

    int i = 1;
    for (; i < argc && argv[i][0] == '-'; i++) {
        for (int j = 1; argv[i][j]; j++) {
            if (argv[i][j] == 'r') recursive = 1;
            else if (argv[i][j] == 'f') force = 1;
            else if (argv[i][j] == 'v') verbose = 1;
            else {
                printf("알 수 없는 옵션: -%c\n", argv[i][j]);
                return;
            }
        }
    }

    for (; i < argc; i++) {
        delete_node(tree->current, argv[i], recursive, force, verbose);
    }
}
