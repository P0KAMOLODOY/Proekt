#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>

FILE* fs_open_or_create(const char* filename);
char* fs_view_file(const char* filename);
int fs_delete_file(const char* filename);

#endif
