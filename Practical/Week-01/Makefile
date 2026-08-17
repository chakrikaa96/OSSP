CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c src/shell.c src/parser.c src/executor.c src/builtin.c
OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = bin/my_shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o bin/my_shell
