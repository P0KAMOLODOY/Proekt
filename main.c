CC = gcc
CFLAGS = -Wall -Wextra
TARGET = fs_project
SRC = src/filesystem.c

all: $(TARGET)

$(TARGET): $(SRC)
 $(CC) $(CFLAGS) -o $@ $^

clean:
 rm -f $(TARGET)

.PHONY: all clean
