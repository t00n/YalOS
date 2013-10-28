#!/bin/zsh
nasm -felf boot.s -o boot.o
i586-elf-gcc -c term.c -o term.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i586-elf-gcc -c system.c -o system.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i586-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i586-elf-gcc -T linker.ld -o alos.bin -ffreestanding -O2 -nostdlib *.o -lgcc
qemu-system-i386 -kernel alos.bin
