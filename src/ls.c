#include <stdio.h>
#include <string.h>
#include "../include/ls.h"

extern DTree* tree;//��üƮ��

void print_permissions(int permission[9]) {
    const char* rwx = "rwx";
    for (int i = 0; i < 9; i++) {
        printf("%c", permission[i] ? rwx[i % 3] : '-');
    }
}

void command_ls(int argc, char** argv) {//������ �Լ��� ls,ls-a,ls-al�� ���� �������� �ʰ�
    int show_all = 0, long_format = 0;//�ѹ��� ���� + ������ ls-la���� ����

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) show_all = 1;
        else if (strcmp(argv[i], "-l") == 0) long_format = 1;
        else if (strcmp(argv[i], "-al") == 0 || strcmp(argv[i], "-la") == 0)
            show_all = long_format = 1;
    }

    TNode* node = tree->current->left;
    while (node != NULL) {
        if (!show_all && node->name[0] == '.') {
            node = node->right;
            continue;
        }

        if (long_format) {
            printf("%c", node->type);
            print_permissions(node->permission);
            printf(" %d %d %5d %02d-%02d %02d:%02d %s\n",
                node->UID, node->GID, node->SIZE,
                node->month, node->day, node->hour, node->minute,
                node->name);
        }
        else {
            printf("%s  ", node->name);
        }

        node = node->right;
    }

    if (!long_format) printf("\n");
}
