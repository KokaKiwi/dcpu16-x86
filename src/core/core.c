#include "kernel.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "dcpu/emulator.h"
#include "dcpu/hardware.h"
#include "core.h"

//#define __DEBUG__

uchar dcpu16_running = 1;

void kernel()
{
    dcpu16_t *cpu = (dcpu16_t *) 0x100000;
    
    print("Initializing DCPU-16...");
    dcpu16_init(cpu);
    ok_msg();
    
    print("Initializing DCPU-16 devices...");
    dcpu16_loadhardware(cpu);
    ok_msg();
    
    print("Loading DCPU-16 program...");
    dcpu16_ramcpy(cpu, &dcpu_program_start, 0,
            (unsigned long int) &dcpu_program_size);
    ok_msg();
    
    println("Starting DCPU-16...");
    
    show_cursor();
    
    while (dcpu16_running)
    {
        dcpu16_step(cpu);
        dcpu16_trigger_interrupt(cpu);
        dcpu16_tickhardware(cpu);
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
}

#define HARDWARE_DESCRIPTORS
dcpu16_hardware_descriptor_t *hardwares[] = {
#include "dcpu/hardware.h"
        };
#undef HARDWARE_DESCRIPTORS

void dcpu16_loadhardware(dcpu16_t *cpu)
{
    u16 i;
    
    for (i = 0; i < HARDWARE_COUNT; i++)
    {
        if (hardwares[i])
        {
            cpu->hardware[i].descriptor = *hardwares[i];
            cpu->hardware[i].present = 1;
            
            if (hardwares[i]->init)
            {
                hardwares[i]->init(cpu, &cpu->hardware[i]);
            }
        }
    }
}

void dcpu16_tickhardware(dcpu16_t *cpu)
{
    u16 i;
    
    for (i = 0; i < HARDWARE_COUNT; i++)
    {
        if (hardwares[i] && cpu->hardware[i].present
                && cpu->hardware[i].descriptor.tick)
        {
            cpu->hardware[i].descriptor.tick(cpu, &cpu->hardware[i]);
        }
    }
}
