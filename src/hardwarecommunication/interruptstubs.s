.set IRQ_BASE, 0x20

.section .text

.extern _ZN7andoros21hardwarecommunication16InterruptManager15HandleInterruptEhj

.macro HandleException num
.global _ZN16InterruptManager16HandleInterruptException\num\()Ev
_ZN16InterruptManager16HandleInterruptException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN7andoros21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN7andoros21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm


HandleInterruptRequest 0x00 
HandleInterruptRequest 0x01 
HandleInterruptRequest 0x0C 

int_bottom:

    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptnumber)
    call _ZN7andoros21hardwarecommunication16InterruptManager15HandleInterruptEhj
    add %esp, 6
    movl %eax, %esp
    
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

.global _ZN7andoros21hardwarecommunication16InterruptManager15InterruptIgnoreEv
_ZN7andoros21hardwarecommunication16InterruptManager15InterruptIgnoreEv:

    iret
.data
    interruptnumber: .byte 0
