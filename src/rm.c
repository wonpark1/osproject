#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/osproject.h"
#include "../include/command.h"

void delete_node(DTree* dTree, const char* path, int recursive, int force, int verbose) {
    TNode* currentN = dTree->current;
    TNode* target = NULL;
    TNode* tmpDir = NULL;
    char tmp[MAXDIRECTORY];
    char tmp2[MAXDIRECTORY];
    char tmp3[MAXDIRECTORY];
    char* str;
    int val;

    strncpy(tmp, path, MAXDIRECTORY);

    // ��ΰ� ���Ե� ���
    if (strchr(path, '/')) {
        strncpy(tmp2, getDir(path), MAXDIRECTORY);
        val = MovePath(dTree, tmp2);
        if (val != 0) {
            if (!force)
                printf("rm: '%s': �׷� �����̳� ���͸��� �����ϴ�.\n", tmp2);
            return;
        }

        str = strtok(tmp, "/");
        while (str != NULL) {
            strncpy(tmp3, str, MAXNAME);
            str = strtok(NULL, "/");
        }
    }
    else {
        strncpy(tmp3, path, MAXNAME);
    }

    // ���͸����� �������� �Ǻ�
    target = ExistDir(dTree, tmp3, 'd');
    if (target && !recursive) {
        if (!force)
            printf("rm: ���丮 '%s'�� ������� -r �ɼ��� �ʿ��մϴ�.\n", tmp3);
        dTree->current = currentN;
        return;
    }
    if (!target) {
        target = ExistDir(dTree, tmp3, 'f');
    }

    if (!target) {
        if (!force)
            printf("rm: '%s': �׷� �����̳� ���͸��� �����ϴ�.\n", tmp3);
        dTree->current = currentN;
        return;
    }

    // ���� Ȯ��
    if (!force && (IsPermission(dTree->current, 'w') != 0 || IsPermission(target, 'w') != 0)) {
        printf("rm: '%s'��(��) ���� �� �����ϴ�: Permission denied\n", tmp3);
        dTree->current = currentN;
        return;
    }

    // ��� ���� ó��
    if (target->type == 'd' && recursive) {
        while (target->left)
            delete_node(dTree, target->left->name, recursive, force, verbose);
    }

    // ���� ����
    if (verbose)
        printf("������: %s\n", tmp3);
    RemoveDir(dTree, tmp3);

    dTree->current = currentN;  // ����ġ ����
}

void command_rm(DTree* tree, int argc, char** argv) {
    int recursive = 0, force = 0, verbose = 0;

    int i = 1;
    for (; i < argc && argv[i][0] == '-'; i++) {
        for (int j = 1; argv[i][j]; j++) {
            if (argv[i][j] == 'r') recursive = 1;
            else if (argv[i][j] == 'f') force = 1;
            else if (argv[i][j] == 'v') verbose = 1;
            else {
                printf("rm: �� �� ���� �ɼ� -- '%c'\n", argv[i][j]);
                return;
            }
        }
    }

    for (; i < argc; i++) {
        delete_node(tree, argv[i], recursive, force, verbose);
    }
}
