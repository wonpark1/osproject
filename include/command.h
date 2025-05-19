#ifndef COMMAND_H
#define COMMAND_H
#include "include/osproject.h"


void command_ls(int argc, char** argv);
void command_mkdir(int argc, char** argv);
void command_cat(DTree* tree, const char* filename);
void command_alias(AliasTable* table, int argc, char** argv);
void command_rm(int argc, char** argv);

#endif
