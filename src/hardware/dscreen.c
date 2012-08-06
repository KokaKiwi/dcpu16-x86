#include "dcpu/hardware/dscreen.h"

dcpuw_t dcpu16_screen[DCPU16_SCREEN_LENGTH];

int dcpu16_screen_interrupt(dcpu16_t *cpu, dcpu16_hardware_t *screen)
{
    dcpuw_t a = cpu->registers[DCPU16_REG_A];
    dcpuw_t b = cpu->registers[DCPU16_REG_B];
    dcpuw_t c = cpu->registers[DCPU16_REG_C];
    
    switch (a)
    {
    
    }
    
    cpu->registers[DCPU16_REG_A] = a;
    cpu->registers[DCPU16_REG_B] = b;
    cpu->registers[DCPU16_REG_C] = c;
    
    return 0;
}

dcpu16_hardware_descriptor_t dcpu16_screen_hardware = { 0x7349f615, 0x1802,
        0x1c6c8b36, 0, dcpu16_screen_interrupt, 0 };
