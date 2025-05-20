#ifndef COMMAND_H
#define COMMAND_H

#include "include/osproject.h"

void command_ls(DTree* tree, int argc, char** argv);
void command_mkdir(DTree* tree, int argc, char** argv);
void command_cat(DTree* tree, const char* filename);
void command_alias(AliasTable* table, int argc, char** argv);
void command_rm(DTree* tree, int argc, char** argv);

int command_cd(DTree* tree, UList* users, int argc, char** argv);
int command_pwd(DTree* tree, Stack* stack, UList* users);
int command_cp(DTree* tree, int argc, char** argv);

int cd(DTree* tree, char* command);
int MovePath(DTree* tree, char* path);
int Movecurrent(DTree* tree, char* segment);

int pwd(DTree* tree, Stack* stack, char* opt);
int PrintPath(DTree* tree, Stack* stack);
int cp(DTree* tree, char* src, char* dst);

void UpdateUserDir(UList* users, DTree* tree);

#endif
