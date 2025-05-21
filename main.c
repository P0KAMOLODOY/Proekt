#include "filesystem.h"
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 256
#define MAX_PARAMS 3

void process_command(char* cmd, char* params[]) {
    if (strcmp(cmd, "создать") == 0 && params[0]) {
        fs_create_file(params[0], params[1] ? params[1] : "");
        printf("Файл %s создан\n", params[0]);
    }
    else if (strcmp(cmd, "удалить") == 0 && params[0]) {
        fs_delete_file(params[0]);
        printf("Файл %s удален\n", params[0]);
    }
    else if (strcmp(cmd, "изменить") == 0 && params[0] && params[1]) {
        fs_update_file(params[0], params[1]);
        printf("Файл %s изменен\n", params[0]);
    }
    else if (strcmp(cmd, "просмотреть") == 0 && params[0]) {
        char* content = fs_read_file(params[0]);
        printf("Содержимое: %s\n", content ? content : "(файл пуст или не существует)");
        free(content);
    }
    else {
        printf("Неизвестная команда или неверные параметры\n");
    }
}

int main() {
    fs_init();
    printf("Добро пожаловать в файловую систему!\n");
    printf("Доступные команды:\n");
    printf("создать <имя> [содержимое]\n");
    printf("удалить <имя>\n");
    printf("изменить <имя> <новое_содержимое>\n");
    printf("просмотреть <имя>\n");
    printf("выход - для завершения\n\n");

    while(1) {
        printf("> ");
        char input[MAX_INPUT];
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0; // Удаляем \n

        if (strcmp(input, "выход") == 0) break;

        char* token = strtok(input, " ");
        char* params[MAX_PARAMS] = {NULL};
        
        if (token) {
            char* cmd = token;
            int i = 0;
            while ((token = strtok(NULL, " ")) && i < MAX_PARAMS-1) {
                params[i++] = token;
            }
            process_command(cmd, params);
        }
    }
    
    return 0;
}
