#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Структура виртуального файла */
typedef struct {
    char* name;
    char* content;
    size_t size;
} VirtualFile;

/* Инициализация файловой системы */
void fs_init();

/* Создание/открытие файла */
FILE* fs_open_or_create(const char* filename);

/* Чтение содержимого файла */
char* fs_read_file(const char* filename);

/* Создание нового файла */
int fs_create_file(const char* filename, const char* content);

/* Удаление файла */
int fs_delete_file(const char* filename);

/* Изменение содержимого файла */
int fs_update_file(const char* filename, const char* new_content);

#endif
