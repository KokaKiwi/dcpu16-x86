#include "dcpu/emulator.h"
#include "dcpu/dcpu_opcodes.h"
#include "dcpu/basic_opcodes.h"
#include "types.h"

uchar dcpu16_handle_opSET(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw);
    return 1;
}

uchar dcpu16_handle_opADD(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if ((int) *bw + (int) *aw > 0xffff)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 1);
    }
    else
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    dcpu16_set(cpu, bw, *bw + *aw);
    
    return 2;
}

uchar dcpu16_handle_opSUB(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if ((int) *bw - (int) *aw < 0)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0xffff);
    }
    else
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    dcpu16_set(cpu, bw, *bw - *aw);
    
    return 2;
}

uchar dcpu16_handle_opMUL(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
            (((*bw) * (*aw)) >> 16) & 0xffff);
    dcpu16_set(cpu, bw, (*bw) * (*aw));
    
    return 2;
}

uchar dcpu16_handle_opMLI(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
            ((((dcpusw_t) *bw) * ((dcpusw_t) *aw)) >> 16) & 0xffff);
    dcpu16_set(cpu, bw, (*bw) * (*aw));
    
    return 2;
}

uchar dcpu16_handle_opDIV(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if (*aw)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
                ((*bw << 16) / *aw) & 0xffff);
        dcpu16_set(cpu, bw, *bw / *aw);
    }
    else
    {
        dcpu16_set(cpu, bw, 0);
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    return 3;
}

uchar dcpu16_handle_opDVI(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if ((dcpusw_t) *aw)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
                (((dcpusw_t) *bw << 16) / (dcpusw_t) *aw) & 0xffff);
        dcpu16_set(cpu, bw, (dcpusw_t) *bw / (dcpusw_t) *aw);
    }
    else
    {
        dcpu16_set(cpu, bw, 0);
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    return 3;
}

uchar dcpu16_handle_opMOD(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if (*aw)
    {
        dcpu16_set(cpu, bw, *bw % *aw);
    }
    else
    {
        dcpu16_set(cpu, bw, 0);
    }
    
    return 3;
}

uchar dcpu16_handle_opMDI(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if (*aw)
    {
        dcpu16_set(cpu, bw, (dcpusw_t) *bw % (dcpusw_t) *aw);
    }
    else
    {
        dcpu16_set(cpu, bw, 0);
    }
    
    return 3;
}

uchar dcpu16_handle_opAND(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw & *bw);
    
    return 1;
}

uchar dcpu16_handle_opBOR(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw | *bw);
    
    return 1;
}

uchar dcpu16_handle_opXOR(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw ^ *bw);
    
    return 1;
}

uchar dcpu16_handle_opSHR(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
            ((*bw << 16) >> *aw) & 0xffff);
    dcpu16_set(cpu, bw, *bw >> *aw);
    
    return 1;
}

uchar dcpu16_handle_opASR(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
            (((dcpusw_t) *bw << 16) >> (dcpusw_t) *aw) & 0xffff);
    dcpu16_set(cpu, bw, (dcpusw_t) *bw >> (dcpusw_t) *aw);
    
    return 1;
}

uchar dcpu16_handle_opSHL(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX],
            ((*bw << *aw) >> 16) & 0xffff);
    dcpu16_set(cpu, bw, *bw << *aw);
    
    return 1;
}

uchar dcpu16_handle_opIFB(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (!(*aw & *bw))
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFC(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (*aw & *bw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFE(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (*aw != *bw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFN(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (*aw == *bw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFG(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (*bw <= *aw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFA(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if ((dcpusw_t) *bw <= (dcpusw_t) *aw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFL(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if (*bw >= *aw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opIFU(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    uchar cycles = 2;
    
    if ((dcpusw_t) *bw <= (dcpusw_t) *aw)
    {
        dcpu16_skip_next_instruction(cpu);
        cycles++;
    }
    
    return cycles;
}

uchar dcpu16_handle_opADX(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if ((int) *bw + (int) *aw + (int) cpu->registers[DCPU16_REG_EX] > 0xffff)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 1);
    }
    else
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    dcpu16_set(cpu, bw, *bw + *aw + cpu->registers[DCPU16_REG_EX]);
    
    return 3;
}

uchar dcpu16_handle_opSBX(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    if ((int) *bw - (int) *aw + (int) cpu->registers[DCPU16_REG_EX] < 0)
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 1);
    }
    else
    {
        dcpu16_set(cpu, &cpu->registers[DCPU16_REG_EX], 0);
    }
    
    dcpu16_set(cpu, bw, *bw - *aw + cpu->registers[DCPU16_REG_EX]);
    
    return 3;
}

uchar dcpu16_handle_opSTI(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw);
    cpu->registers[DCPU16_REG_I]++;
    cpu->registers[DCPU16_REG_J]++;
    
    return 2;
}

uchar dcpu16_handle_opSTD(dcpu16_t *cpu, uchar a, uchar b, dcpuw_t *aw,
        dcpuw_t *bw)
{
    dcpu16_set(cpu, bw, *aw);
    cpu->registers[DCPU16_REG_I]--;
    cpu->registers[DCPU16_REG_J]--;
    
    return 2;
}
