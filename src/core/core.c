#include "kernel.h"
#include "stdio.h"
#include "stdarg.h"
#include "emulator.h"
#include "core.h"

//dcpu16_t *cpu = (dcpu16_t *) 0xb0000;
dcpu16_t dcpu;

#define __DEBUG__

void kernel()
{
    dcpuw_t *p = (dcpuw_t *) &dcpu_program_start;
    char *c = (char *) &dcpu_program_start;
    unsigned long int size = (unsigned long int) &dcpu_program_size;
    dcpu16_t *cpu = (dcpu16_t *) 0xff000;
    u16 i;
    
    print("Initializing DCPU-16...");
    dcpu16_init(cpu);
    ok_msg();
    
    print("Loading DCPU-16 program...");
    dcpu16_ramcpy(cpu, p, 0, size);
//    ok_msg();
//    show_cursor();
    
    printf("[0x%x] = 0x%x\n", &cpu->ram[0], cpu->ram[0]);
    
    for (i = 0; i < 5; i++)
    {
        dcpu16_step(cpu);
    }
    
#ifdef __DEBUG__
    dcpu16_printreg(cpu, "A", DCPU16_REG_A, 1);
    dcpu16_printreg(cpu, "B", DCPU16_REG_B, 1);
    dcpu16_printreg(cpu, "C", DCPU16_REG_C, 1);
    dcpu16_printreg(cpu, "X", DCPU16_REG_X, 1);
    dcpu16_printreg(cpu, "Y", DCPU16_REG_Y, 1);
    dcpu16_printreg(cpu, "Z", DCPU16_REG_Z, 1);
    dcpu16_printreg(cpu, "I", DCPU16_REG_I, 1);
    dcpu16_printreg(cpu, "J", DCPU16_REG_J, 1);
    dcpu16_printreg(cpu, "PC", DCPU16_REG_PC, 1);
    dcpu16_printreg(cpu, "SP", DCPU16_REG_SP, 1);
    dcpu16_printreg(cpu, "IA", DCPU16_REG_IA, 0);
    dcpu16_printreg(cpu, "EX", DCPU16_REG_EX, 0);
#endif
    
    show_cursor();
}
