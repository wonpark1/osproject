#include "include/command.h"

/* 1 KB 버퍼 복사 + 기존 파일 덮어쓰기 또는 삭제 후 재생성 -------------- */
static int cp_file(DTree *dTree, const char *src, const char *dst)
{
    char buf[1024];
    int  in_fd, out_fd, n;

    /* 1) 원본 존재 확인 */
    if (access(src, F_OK) != 0) {
        printf("cp: %s: No such file\n", src);
        return -1;
    }
    /* 2) 동일 파일 검사 */
    if (strcmp(src, dst) == 0) {
        puts("cp: source and destination are the same");
        return -1;
    }
    /* 3) 대상 파일이 존재하면 삭제 후 새로 생성 */
    if (ExistDir(dTree, (char*)dst, 'f'))
        DeleteFile(dTree, (char*)dst);

    /* 4) FD 열기 */
    in_fd  = open(src, O_RDONLY);
    out_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (in_fd < 0 || out_fd < 0) {
        perror("cp: open");
        if (in_fd  >= 0) close(in_fd);
        if (out_fd >= 0) close(out_fd);
        return -1;
    }

    /* 5) 복사 */
    while ((n = read(in_fd, buf, sizeof(buf))) > 0) {
        if (write(out_fd, buf, n) != n) {
            perror("cp: write");
            close(in_fd); close(out_fd);
            return -1;
        }
    }
    close(in_fd); close(out_fd);

    /* 6) 트리 메타 정보 등록 */
    MakeDir(dTree, (char*)dst, 'f');
    return 0;
}

int cp(DTree *dTree, char *src, char *dst)
{
    return cp_file(dTree, src, dst);
}
