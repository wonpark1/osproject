#include "include/command.h"

/* pwd 내부 로직 (스택 방식) --------------------------------------------- */
int pwd(DTree *dTree, Stack *dStack, char *opt)
{
    /* 옵션 검사 */
    if (opt && strcmp(opt, "--help") == 0) {
        puts("Guide : pwd");
        puts("Print the name of the current working directory.");
        return 0;
    }
    if (opt && opt[0] == '-') {
        printf("pwd: invalid option -- '%s'\n", opt);
        puts("Try 'pwd --help' for more information.");
        return -1;
    }

    return PrintPath(dTree, dStack);
}

/* 스택을 이용해 즉석으로 절대경로 생성 후 출력 -------------------------- */
int PrintPath(DTree *dTree, Stack *dStack)
{
    TNode *cursor = dTree->current;

    if (cursor == dTree->root) {
        puts("/");
        return 0;
    }

    /* root까지 Push */
    while (cursor && cursor->Parent) {
        Push(dStack, cursor->name);        /* 이름 저장 */
        cursor = cursor->Parent;
    }

    /* Pop 하며 출력 */
    while (!IsEmpty(dStack)) {
        printf("/%s", Pop(dStack));
    }
    puts("");
    return 0;
}
