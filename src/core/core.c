#include "kernel.h"
#include "stdio.h"
#include "stdarg.h"
#include "emulator.h"
#include "core.h"

dcpu16_t cpu;

void kernel()
{
    dcpuw_t *p = (dcpuw_t *) &dcpu_program_start;
    char *c = (char *) &dcpu_program_start;
    unsigned long int size = (unsigned long int) &dcpu_program_size;
    int i;
    
    print("Loading DCPU-16 program...");
    dcpu16_ramcpy(&cpu, p, 0, size);
    ok_msg();
    
#ifdef __DEBUG__
    dcpu16_printreg(&cpu, "A", DCPU16_REG_A, 1);
    dcpu16_printreg(&cpu, "B", DCPU16_REG_B, 1);
    dcpu16_printreg(&cpu, "C", DCPU16_REG_C, 1);
    dcpu16_printreg(&cpu, "X", DCPU16_REG_X, 1);
    dcpu16_printreg(&cpu, "Y", DCPU16_REG_Y, 1);
    dcpu16_printreg(&cpu, "Z", DCPU16_REG_Z, 1);
    dcpu16_printreg(&cpu, "I", DCPU16_REG_I, 1);
    dcpu16_printreg(&cpu, "J", DCPU16_REG_J, 1);
    dcpu16_printreg(&cpu, "PC", DCPU16_REG_PC, 1);
    dcpu16_printreg(&cpu, "SP", DCPU16_REG_SP, 1);
    dcpu16_printreg(&cpu, "IA", DCPU16_REG_IA, 0);
    dcpu16_printreg(&cpu, "EX", DCPU16_REG_EX, 0);

    print("Dump: ");
    dcpu16_dumpram(&cpu, 16);
    putchar('\n');
#endif
    
    show_cursor();
}
