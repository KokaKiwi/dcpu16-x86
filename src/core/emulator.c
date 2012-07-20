#include "emulator.h"
#include "dcpu_opcodes.h"
#include "stdio.h"
#include "string.h"
#include "endian.h"

#define opcode(handler) handler,

#define BASIC_OPCODES
static basic_opcode_handler basic_opcode_handlers[] = {
#include "dcpu_opcodes.h"
        };
#undef BASIC_OPCODES

#define SPECIAL_OPCODES
static special_opcode_handler special_opcode_handlers[] = {
#include "dcpu_opcodes.h"
        };
#undef SPECIAL_OPCODES

#undef opcode

void dcpu16_set(dcpu16_t *cpu, dcpuw_t *addr, dcpuw_t value)
{
    dcpuw_t ram_address;
    
    if (addr >= cpu->ram && addr < cpu->ram + DCPU16_RAM_SIZE)
    {
        ram_address = addr - cpu->ram;
        
        dcpu16_call_ram_listeners(cpu, ram_address, value);
    }
    else if (addr
            >= cpu->registers&& addr < cpu->registers + DCPU16_REGISTER_COUNT)
    {
        dcpu16_call_register_listeners(cpu, addr - cpu->registers, value);
    }
    
    *addr = value;
}

dcpuw_t *dcpu16_register_pointer(dcpu16_t *cpu, uchar index)
{
    return &cpu->registers[index];
}

uchar dcpu16_get_pointer(dcpu16_t *cpu, uchar addr, dcpuw_t *tmp_storage,
        dcpuw_t **retval, uchar is_a)
{
    uchar cycles = 0;
    
    if (addr <= DCPU16_AB_VALUE_REG_J)
    {   // 0x00-0x07 (value of register)
        *retval = dcpu16_register_pointer(cpu, addr);
    }
    else if (addr <= DCPU16_AB_VALUE_PTR_REG_J)
    {   // 0x08-0x0f (value at address pointed to by register)
        *retval = &cpu->ram[*dcpu16_register_pointer(cpu,
                addr - DCPU16_AB_VALUE_PTR_REG_A)];
    }
    else if (addr <= DCPU16_AB_VALUE_PTR_REG_J_PLUS_WORD)
    { // 0x10-0x17 (value at address pointed to by the sum of the register and the next word)
        *retval = &cpu->ram[(dcpuw_t) (*dcpu16_register_pointer(cpu,
                addr - DCPU16_AB_VALUE_PTR_REG_A_PLUS_WORD)
                + cpu->ram[cpu->registers[DCPU16_REG_PC]++])];
        cycles = 1;
    }
    else if (addr >= 0x20 && addr <= 0x3f)
    {   // 0x20-0x3F (literal value from 0xFFFF to 0x1E (-1 to 30))
        if (tmp_storage)
        {
            *tmp_storage = addr - 0x20 + 0xffff;
        }
        *retval = tmp_storage;
    }
    else
    {
        switch (addr)
        {
            case DCPU16_AB_VALUE_PUSH_OR_POP:
                if (is_a)
                {
                    *retval = &cpu->ram[cpu->registers[DCPU16_REG_SP]++];
                }
                else
                {
                    *retval = &cpu->ram[--cpu->registers[DCPU16_REG_SP]];
                }
                break;
                
            case DCPU16_AB_VALUE_PEEK:
                *retval = &cpu->ram[cpu->registers[DCPU16_REG_SP]];
                break;
                
            case DCPU16_AB_VALUE_PICK:
                *retval = &cpu->ram[cpu->registers[DCPU16_REG_SP]
                        + cpu->ram[cpu->registers[DCPU16_REG_PC]]];
                cycles = 1;
                break;
                
            case DCPU16_AB_VALUE_REG_SP:
                *retval = &cpu->registers[DCPU16_REG_SP];
                break;
                
            case DCPU16_AB_VALUE_REG_PC:
                *retval = &cpu->registers[DCPU16_REG_PC];
                break;
                
            case DCPU16_AB_VALUE_REG_EX:
                *retval = &cpu->registers[DCPU16_REG_EX];
                break;
                
            case DCPU16_AB_VALUE_PTR_WORD:
                *retval = &cpu->ram[cpu->ram[cpu->registers[DCPU16_REG_PC]++]];
                cycles = 1;
                break;
                
            case DCPU16_AB_VALUE_WORD:
                *retval = &cpu->ram[cpu->registers[DCPU16_REG_PC]++];
                cycles = 1;
                break;
        }
    }
    
    return cycles;
}

void dcpu16_call_ram_listeners(dcpu16_t *cpu, dcpuw_t addr, dcpuw_t value)
{
    dcpu16_ram_listener *root, *cur;
    
    root = cur = cpu->listeners.ram_listener;
    
    while (cur && (cur->next != root))
    {
        cur->callback(addr, value);
        cur = cur->next;
    }
}

void dcpu16_call_register_listeners(dcpu16_t *cpu, uchar reg, dcpuw_t value)
{
    dcpu16_register_listener *root, *cur;
    
    root = cur = cpu->listeners.register_listener;
    
    while (cur && (cur->next != root))
    {
        cur->callback(reg, value);
        cur = cur->next;
    }
}

void dcpu16_init(dcpu16_t *cpu)
{
    memset(cpu, 0, sizeof(dcpu16_t));
}

void dcpu16_ramcpy(dcpu16_t *cpu, dcpuw_t *src, dcpuw_t offset, size_t length)
{
    dcpuw_t tmp;
    dcpuw_t *dest = &cpu->ram[offset];
    
    while (length--)
    {
        tmp = *src++;
        
        if (IS_LITTLE_ENDIAN)
        {
            *dest++ = DCPU16_WORD(tmp);
        }
        else
        {
            *dest++ = tmp;
        }
    }
}

uchar dcpu16_step(dcpu16_t *cpu)
{
    uchar cycles = 0;
    dcpuw_t opword;
    uchar opcode, a, b;
    dcpuw_t tmp_a, tmp_b, *aw, *bw;
    dcpuw_t pc;
    
    pc = cpu->registers[DCPU16_REG_PC]++;
    opword = cpu->ram[pc];
    
    opcode = opword & 0x1f;
    
#ifdef __DCPU16_EXEC_DEBUG__
    printf("0x%x: ", pc);
#endif
    
    if (opcode)
    {
        b = (opword >> 5) & 0x1f;
        a = (opword >> 10) & 0x3f;
        
#ifdef __DCPU16_EXEC_DEBUG__
        printf("basic-0x%x", opcode);
#endif
        
        if (basic_opcode_handlers[opcode])
        {
            cycles += dcpu16_get_pointer(cpu, a, &tmp_a, &aw, 1);
            cycles += dcpu16_get_pointer(cpu, b, &tmp_b, &bw, 0);
            
#ifdef __DCPU16_EXEC_DEBUG__
            printf(" a[0x%x] aw[0x%x] - b[0x%x] bw[0x%x]", a, *aw, b, *bw);
#endif
            
            cycles += basic_opcode_handlers[opcode](cpu, a, b, aw, bw);
        }
    }
    else
    {
        opcode = (opword >> 5) & 0x1f;
        a = (opword >> 10) & 0x3f;
        
#ifdef __DCPU16_EXEC_DEBUG__
        printf("special-0x%x", opcode);
#endif
        
        if (special_opcode_handlers[opcode])
        {
            cycles += dcpu16_get_pointer(cpu, a, &tmp_a, &aw, 1);
            
#ifdef __DCPU16_EXEC_DEBUG__
            printf(" a[0x%x] aw[0x%x]", a, *aw);
#endif
            
            cycles += special_opcode_handlers[opcode](cpu, a, aw);
        }
    }
    
#ifdef __DCPU16_EXEC_DEBUG__
    putchar('\n');
#endif
    
    return cycles;
}

void dcpu16_skip_next_instruction(dcpu16_t *cpu)
{
    dcpuw_t opword, opcode, a, b;
    dcpuw_t *aw, *bw;
    
    opword = cpu->ram[cpu->registers[DCPU16_REG_PC]++];
    opcode = opword & 0x1f;
    
    if (opcode)
    {
        b = (opword >> 5) & 0x1f;
        a = (opword >> 10) & 0x3f;
        
        dcpu16_get_pointer(cpu, a, 0, &aw, 1);
        dcpu16_get_pointer(cpu, b, 0, &bw, 0);
    }
    else
    {
        opcode = (opword >> 5) & 0x1f;
        a = (opword >> 10) & 0x3f;
        
        dcpu16_get_pointer(cpu, a, 0, &aw, 1);
    }
}

void dcpu16_printreg(dcpu16_t *cpu, char *name, char index, char print_ptr)
{
    print(name);
    screenX = 3;
    printf(": 0x%x", cpu->registers[index]);
    if (print_ptr)
    {
        screenX = 15;
        printf("[%s]", name);
        screenX = 20;
        printf(": 0x%x", cpu->ram[cpu->registers[index]]);
    }
    putchar('\n');
}

void dcpu16_dumpram(dcpu16_t *cpu, size_t length)
{
    int i;
    
    for (i = 0; i < length; i++)
    {
        printf("%x", cpu->ram[cpu->registers[DCPU16_REG_PC] + i]);
    }
}
