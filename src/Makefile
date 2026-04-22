CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
SRC = read_elf.c
TARGET = read_elf

all: read_elf

read_elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(TARGET) 
	
