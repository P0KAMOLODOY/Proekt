#include <stdio.h>
#include "filesystem.h"

int main() {
    
    FILE* file = fs_open_or_create("test.txt");
    if (file) {
        fprintf(file, "Hello, FileSystem!");
        fclose(file); 
        
        char* content = fs_view_file("test.txt");
        printf("Содержимое: %s\n", content);
        
        fs_delete_file("test.txt");
    }
    return 0;
}
