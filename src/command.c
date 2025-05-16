#include <stdio.h>
#include "include/command.h"

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

