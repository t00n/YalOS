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
	
; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
    lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               ; Returns back to the C code!
    
; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret


global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31


isr0: ; divide by zero exception
	cli
	push byte 0
	push byte 0
	jmp isr_common_stub
isr1: ; debug exception
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub
isr2: ; non maskable interrupt exception
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub
isr3: ; breakpoint exception
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub
isr4: ; into detected overflow exception
	cli
	push byte 0
	push byte 4
	jmp isr_common_stub
isr5: ; out of bounds exception
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub
isr6: ; invalid opcode exception
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub
isr7: ; no coprocessor exception
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub
isr8: ; double fault exception
	cli
	push byte 8
	jmp isr_common_stub
isr9: ; coprocessor segment overrun exception
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub
isr10: ; bad TSS exception
	cli
	push byte 10
	jmp isr_common_stub
isr11: ; segment not present exception
	cli
	push byte 11
	jmp isr_common_stub
isr12: ; stack fault exception
	cli
	push byte 12
	jmp isr_common_stub
isr13: ; general protection fault exception
	cli
	push byte 13
	jmp isr_common_stub
isr14: ; page fault exception
	cli
	push byte 14
	jmp isr_common_stub
isr15: ; unknown interrupt exception
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub
isr16: ; coprocessor fault exception
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub
isr17: ; alignment check exception
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub
isr18: ; machine check exception
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub
isr19: ; reserved exception
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub
isr20: ; reserved exception
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub
isr21: ; reserved exception
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub
isr22: ; reserved exception
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub
isr23: ; reserved exception
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub
isr24: ; reserved exception
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub
isr25: ; reserved exception
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub
isr26: ; reserved exception
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub
isr27: ; reserved exception
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub
isr28: ; reserved exception
	cli
	push byte 0
	push byte 28
	jmp isr_common_stub
isr29: ; reserved exception
	cli
	push byte 0
	push byte 29
	jmp isr_common_stub
isr30: ; reserved exception
	cli
	push byte 0
	push byte 30
	jmp isr_common_stub
isr31: ; reserved exception
	cli
	push byte 0
	push byte 31
	jmp isr_common_stub
	
extern fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub
irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_common_stub
irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_common_stub
irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_common_stub
irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_common_stub
irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_common_stub
irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_common_stub
irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_common_stub
irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_common_stub
irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_common_stub
irq10:
	cli
	push byte 0
	push byte 42
	jmp irq_common_stub
irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_common_stub
irq12:
	cli
	push byte 0
	push byte 44
	jmp irq_common_stub
irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_common_stub
irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_common_stub
irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_common_stub

extern irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
