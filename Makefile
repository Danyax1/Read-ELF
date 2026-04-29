CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -Iinclude
SRC = $(wildcard src/*.c)
TARGET = read_elf

all: read_elf

read_elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET) 
	
.PHONY: all clean
