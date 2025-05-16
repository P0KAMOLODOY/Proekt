#include <stdio.h>
#include "filesystem.h"

int main() {
    // Тест работы файловой системы
    FILE* file = fs_open_or_create("test.txt");
    if (file) {
        // Записываем что-то в файл (если нужно)
        fprintf(file, "Hello, FileSystem!");
        fclose(file);  // Не забываем закрыть файл
        
        // Читаем содержимое
        char* content = fs_view_file("test.txt");
        printf("Содержимое: %s\n", content);
        
        // Удаляем файл
        fs_delete_file("test.txt");
    }
    return 0;
}
