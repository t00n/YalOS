SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o) boot.o
EXEC=alos.bin
CC=i686-elf-gcc
CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

all: $(SRC) boot.s $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ -T linker.ld $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	nasm -felf boot.s -o boot.o

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper: clean
	rm $(EXEC)