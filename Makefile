SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o) boot.o
EXEC=alos.bin
CC=i686-elf-gcc
CFLAGS=-c -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc

run: all
	qemu-system-i386 -kernel $(EXEC) -m 3G

all: $(SRC) boot.s $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ -T linker.ld $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	nasm -felf $< -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper: clean
	rm $(EXEC)
