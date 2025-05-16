#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"

#define MAX_FILES 100
#define MAX_CONTENT_SIZE 1024

typedef struct {
    char name[50];
    char content[MAX_CONTENT_SIZE];
} File;

static File virtual_fs[MAX_FILES];
static int file_count = 0;

FILE* fs_open_or_create(const char* filename) {
    if (file_count >= MAX_FILES) {
        fprintf(stderr, "Достигнут лимит файлов!\n");
        return NULL;
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(virtual_fs[i].name, filename) == 0) {
            return fopen(filename, "r+");  
        }
    }

    strncpy(virtual_fs[file_count].name, filename, 49);
    virtual_fs[file_count].content[0] = '\0';
    file_count++;

    return fopen(filename, "w+");  
}

char* fs_view_file(const char* filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(virtual_fs[i].name, filename) == 0) {
            return virtual_fs[i].content;
        }
    }
    return NULL; 
}

int fs_delete_file(const char* filename) {
    int found = 0;
    for (int i = 0; i < file_count; i++) {
        if (strcmp(virtual_fs[i].name, filename) == 0) {
            found = 1;
            for (int j = i; j < file_count - 1; j++) {
                strcpy(virtual_fs[j].name, virtual_fs[j+1].name);
                strcpy(virtual_fs[j].content, virtual_fs[j+1].content);
            }
            file_count--;
            break;
        }
    }
    return found ? 0 : -1;  
