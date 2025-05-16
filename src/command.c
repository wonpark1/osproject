#include <stdio.h>
#include <string.h>
#include "include/command.h"
#include "include/osproject.h"


TNode* FindFileInCurrentDir(TNode* current, const char* name) {
    TNode* cursor = current->left;
    while (cursor) {
        if (strcmp(cursor->name, name) == 0 && cursor->type == 'f') {
            return cursor;
        }
        cursor = cursor->right;
    }
    return NULL;
}


void command_ls(int argc, char** argv) {
    printf("📁 executing 'ls'\n");
    // 여기서 디렉토리 트리를 탐색
}

void command_mkdir(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: mkdir <dir_name>\n");
        return;
    }
    printf("🌲 creating directory: %s\n", argv[1]);
    // 여기서 디렉토리 생성 로직을 넣으면 됨
}

void command_cat(DTree* tree, const char* filename) {
    TNode* currentDir = tree->current;
    TNode* file = FindFileInCurrentDir(currentDir, filename);

    if (file == NULL) {
        printf("❌ 파일 '%s'을(를) 찾을 수 없습니다.\n", filename);
        return;
    }

    if (file->type != 'f') {
        printf("⚠️ '%s'은(는) 디렉토리입니다.\n", filename);
        return;
    }

    if (file->SIZE == 0) {
        printf("📄 (빈 파일입니다)\n");
        return;
    }

    // 임시로 내용 하드코딩
    printf("📄 파일 내용 (%s):\n", file->name);
    printf("Hello, this is test content for %s!\n", file->name);
}

void command_alias(AliasTable* table, int argc, char** argv) {
    if (argc == 1) {
        // 모든 alias 출력
        for (int i = 0; i < table->count; i++) {
            printf("alias %s='%s'\n", table->list[i].name, table->list[i].command);
        }
        return;
    }

    if (argc >= 2) {
        // 예: alias ll='ls -al'
        char* equal = strchr(argv[1], '=');
        if (!equal) {
            printf("❌ 올바른 alias 형식이 아닙니다.\n");
            return;
        }

        // name 추출
        int nameLen = equal - argv[1];
        char name[32] = {0};
        strncpy(name, argv[1], nameLen);

        // 'ls -al' 에서 따옴표 제거
        char* commandStr = equal + 1;
        if (commandStr[0] == '\'' || commandStr[0] == '"') commandStr++;
        if (commandStr[strlen(commandStr) - 1] == '\'' || commandStr[strlen(commandStr) - 1] == '"')
            commandStr[strlen(commandStr) - 1] = '\0';

        // 테이블에 저장
        if (table->count < MAX_ALIAS) {
            strcpy(table->list[table->count].name, name);
            strcpy(table->list[table->count].command, commandStr);
            table->count++;
        } else {
            printf("⚠️ alias 최대 개수를 초과했습니다.\n");
        }
    }
}