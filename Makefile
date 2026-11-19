CC = gcc
CFLAGS = -Wall -Wextra
	
SRC = main.c produto.c hash.c abb.c
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(SRC) produto.h hash.h abb.h
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	.\$(TARGET)

clean:
	del /Q $(TARGET)

.PHONY: all run clean