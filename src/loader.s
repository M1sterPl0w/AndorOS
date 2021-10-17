# Bootloader creates multiboat (struct) contains information about RAM size e.g. Multiboat struct's pointer is stored in AX register.
# And the magixnumber in the BX register. 16-bit, in 32-bit it would be EAX and EBX
# https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm

.set MAGIC, 0x1badb002 # magic number: 0x  the bootloader will accept kernel with this number
.set FLAGS, (1<<0 | 1<<1) # also needed for the bootloader
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot # this section puts compiler variables in object file
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain
.extern callConstructors
.global loader

loader:
    mov $kernel_stack, %esp # Set stack pointer

    call callConstructors

    push %eax
    push %ebx
    call kernelMain  # it will never go out but just in case stop section

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024 # 2MB space for before stack pointer
kernel_stack:
