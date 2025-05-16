#include "include/command.h"
#include "include/parser.h"
#include "include/osproject.h"  // DTree, Stack, UList, AliasTable 포함
#include <stdio.h>
#include <string.h>

int main() {
    char cmd[256];

    // 🌱 시스템 초기화
    DTree* tree = DLoad();                // 디렉토리 구조 불러오기
    Stack* stack = StackInit();           // 디렉토리 경로 추적용 스택
    UList* users = UserListLoad();        // 사용자 목록 불러오기
    AliasTable aliasTable = {.count = 0}; // alias 저장 공간

    // 👤 로그인 처리
    Login(users, tree);
    UserListSave(users);

    printf("🌿 Welcome to the Mini OS Shell 🌿\n");
    printf("Type your command below (type 'exit' to quit):\n");

    while (1) {
        PrintHeader(tree, stack, users);  // ex) yeonwoo@home:~$
        printf("myos$ ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "exit") == 0) break;

        // 명령어 파싱 및 실행 (alias 포함)
        ParseAndExecute(tree, stack, users, &aliasTable, cmd);
    }

    return 0;
}
