#include "emulator.h"
#include "special_opcodes.h"
#include "types.h"

uchar dcpu16_handle_opJSR(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    cpu->registers[DCPU16_REG_SP]--;
    cpu->ram[cpu->registers[DCPU16_REG_SP]] = cpu->registers[DCPU16_REG_PC];
    
    cpu->registers[DCPU16_REG_PC] = *aw;
    
    return 3;
}

uchar dcpu16_handle_opINT(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    dcpu16_interrupt(cpu, *aw, 1);
    
    return 4;
}

uchar dcpu16_handle_opIAG(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    dcpu16_set(cpu, aw, cpu->registers[DCPU16_REG_IA]);
    
    return 1;
}

uchar dcpu16_handle_opIAS(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_IA], *aw);
    
    return 1;
}

uchar dcpu16_handle_opRFI(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    // Pop A and PC
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_A],
            cpu->ram[cpu->registers[DCPU16_REG_SP]++]);
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_PC],
            cpu->ram[cpu->registers[DCPU16_REG_SP]++]);
    
    // Enable interrupts
    cpu->interrupts_enabled = 1;
    
    return 3;
}

uchar dcpu16_handle_opIAQ(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    if (*aw)
    {
        cpu->interrupts_enabled = 0;
    }
    else
    {
        cpu->interrupts_enabled = 1;
    }
    
    return 2;
}

uchar dcpu16_handle_opHWN(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    dcpuw_t connected_hardwares = 0;
    u16 i;
    
    for (i = 0; i < DCPU16_HARDWARE_SLOTS; i++)
    {
        if (cpu->hardware[i].present)
        {
            connected_hardwares++;
        }
    }
    
    dcpu16_set(cpu, aw, connected_hardwares);
    show_cursor();
    
    return 2;
}

uchar dcpu16_handle_opHWQ(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    dcpuw_t hardware_index;
    dcpu16_hardware_t *hardware;
    
    hardware_index = cpu->registers[DCPU16_REG_A];
    if (hardware_index >= 0 && hardware_index < DCPU16_HARDWARE_SLOTS
            && (hardware = &cpu->hardware[hardware_index])->present)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_A],
                (dcpuw_t) (hardware->id & 0xffff));
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_B],
                (dcpuw_t) ((hardware->id >> 16) & 0xffff));
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_C],
                (dcpuw_t) hardware->version);
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_X],
                (dcpuw_t) (hardware->manufacturer & 0xffff));
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_Y],
                (dcpuw_t) ((hardware->manufacturer >> 16) & 0xffff));
    }
    
    return 4;
}

uchar dcpu16_handle_opHWI(dcpu16_t *cpu, uchar a, dcpuw_t *aw)
{
    uchar cycles = 4;
    
    dcpuw_t hardware_index;
    dcpu16_hardware_t *hardware;
    
    hardware_index = cpu->registers[DCPU16_REG_A];
    
    if (hardware_index >= 0 && hardware_index < DCPU16_HARDWARE_SLOTS
            && (hardware = &cpu->hardware[hardware_index])->present
            && hardware->interrupt)
    {
        cycles += hardware->interrupt(cpu, hardware);
    }
    
    return cycles;
}
