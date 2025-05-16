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
/**
 * Создает новый файл в виртуальной файловой системе
 * @param fs_content Указатель на содержимое всей ФС
 * @param filename Имя создаваемого файла
 * @param content Содержимое файла
 * @return Указатель на обновленное содержимое ФС
 */
char* fs_create_file(char* fs_content, const char* filename, const char* content) {
    // Вычисляем новую длину
    size_t new_len = strlen(fs_content) + strlen(filename) + strlen(content) + 4;
    
    // Выделяем память
    char* new_fs = malloc(new_len);
    sprintf(new_fs, "%s%s\n%s\n/\n", fs_content, filename, content);
    
    return new_fs;
}
/**
 * Изменяет содержимое существующего файла
 * @param fs_content Указатель на содержимое всей ФС
 * @param filename Имя изменяемого файла
 * @param new_content Новое содержимое файла
 * @return Указатель на обновленное содержимое ФС
 */
char* fs_modify_file(char* fs_content, const char* filename, const char* new_content) {
    char* file_start = strstr(fs_content, filename);
    if (!file_start) return NULL;

    // Находим начало и конец старого содержимого
    char* content_start = file_start + strlen(filename) + 1;
    char* content_end = strstr(content_start, "/\n");
    if (!content_end) content_end = fs_content + strlen(fs_content);

    // Вычисляем новые размеры
    size_t prefix_len = content_start - fs_content;
    size_t suffix_len = strlen(content_end);
    size_t new_len = prefix_len + strlen(new_content) + suffix_len + 1;

    // Собираем новое содержимое
    char* new_fs = malloc(new_len);
    memcpy(new_fs, fs_content, prefix_len);
    strcpy(new_fs + prefix_len, new_content);
    strcpy(new_fs + prefix_len + strlen(new_content), content_end);
    
    return new_fs;
}
