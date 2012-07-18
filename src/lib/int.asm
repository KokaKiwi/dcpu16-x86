extern _isr_default_int, _isr_GP_exec, _isr_PF_exec, _isr_clock_int, _isr_keyboard_int
global _asm_default_int, _asm_exec_GP, _asm_exec_PF, _asm_irq_0, _asm_irq_1

%macro SAVE_REGS 0
    pushad
    push ds
    push es
    push fs
    push gs
    push ebx
    mov bx, 0x10
    mov ds, bx
    pop ebx
%endmacro

%macro RESTORE_REGS 0
    pop gs
    pop fs
    pop es
    pop ds
    popad
%endmacro

_asm_default_int:
    SAVE_REGS
    call _isr_default_int
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret

_asm_exec_GP:
    SAVE_REGS
    call _isr_GP_exec
    RESTORE_REGS
    add esp, 4
    iret

_asm_exec_PF:
    SAVE_REGS
    call _isr_PF_exec
    RESTORE_REGS
    add esp, 4
    iret

_asm_irq_0:
    SAVE_REGS
    call _isr_clock_int
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret

_asm_irq_1:
    SAVE_REGS
    call _isr_keyboard_int
    mov al, 0x20
    out 0x20, al
    RESTORE_REGS
    iret