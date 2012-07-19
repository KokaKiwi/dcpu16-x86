#include "kernel.h"
#include "stdio.h"
#include "emulator.h"
#include "core.h"

dcpu16_t cpu;

void kernel()
{
    printf("DCPU Program size: %d\n%d - %d\n%d", dcpu_program_size, dcpu_program, dcpu_program_end, dcpu_program - dcpu_program_end);
    //memcpy(cpu.ram, dcpu_program, dcpu_program_size);
    
    //dcpu16_step(&cpu);
    
    show_cursor();
}
