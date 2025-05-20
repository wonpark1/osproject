#ifndef OSPROJECT_H
#define OSPROJECT_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#ifndef MAXDIRECTORY
#define MAXDIRECTORY 1024
#endif


typedef struct _tnode {
    char  name[MAXDIRECTORY];   /* 파일/디렉터리 이름          */
    char  type;                
    struct _tnode *left, *right, *Parent;
} TNode;

typedef struct {
    TNode *root;                /* 루트 노드 ("/")             */
    TNode *current;             /* 현재 작업 디렉터리          */
} DTree;


typedef struct _unode {
    char  dir[MAXDIRECTORY];    /* 절대 경로 문자열 (pwd용)    */
    struct _unode *next;
} UNode;

typedef struct {
    UNode *head;
    UNode *current;             /* 로그인 중인 사용자          */
} UList;


typedef struct {
    char dummy;
} AliasTable;

/* ── 외부 API 프로토타입 (stub) ───────────── */
TNode *ExistDir   (DTree *tree, const char *name, char type);
int    IsPermission(TNode *node, char perm);          /* r/w/x → 0 = 허용 */
int    MakeDir     (DTree *tree, char *name, char type);
int    DeleteFile  (DTree *tree, char *name);

#endif /* OSPROJECT_H */
