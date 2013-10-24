; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot
 
; Declare a header as in the Multiboot Standard. We put this into a special
; section so we can force the header to be in the start of the final program.
; You don't need to understand all these details as it is just magic values that
; is documented in the multiboot standard. The bootloader will search for this
; magic sequence and recognize us as a multiboot kernel.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
; initializing 16K stack
section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:
 
; _start is the entry point to the kernel -> see linker.ld
section .text
global _start
_start:
	; set up stack
	mov esp, stack_top
 
	; call C code
	extern kernel_main
	call kernel_main
 
	; Disable interrupts ; halt computer until interrupt ; infinite loop
	cli
.hang:
	hlt
	jmp .hang
