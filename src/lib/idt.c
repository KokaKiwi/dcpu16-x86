#include "idt.h"

IDTR kidtr;
IDTDesc kidt[IDTSIZE];

void init_idt_desc(u16 select, u32 offset, u16 type, IDTDesc *desc)
{
    desc->offset_0_15 = (offset & 0xffff);
    desc->offset_16_31 = (offset & 0xffff0000) >> 16;
    desc->select = select;
    desc->type = type;
    return;
}

void init_idt()
{
    unsigned i;
    
    for (i = 0; i < IDTSIZE; i++)   // default
    {
        init_idt_desc(0x08, (u32) asm_default_int, INTGATE, &kidt[i]);
    }
    
    init_idt_desc(0x08, (u32) asm_exec_GP, INTGATE, &kidt[13]);     // #GP
    init_idt_desc(0x08, (u32) asm_exec_PF, INTGATE, &kidt[14]);     // #PF
            
    init_idt_desc(0x08, (u32) asm_irq_0, INTGATE, &kidt[32]);       // clock
    init_idt_desc(0x08, (u32) asm_irq_1, INTGATE, &kidt[33]);       // keyboard
            
    kidtr.limit = IDTSIZE * sizeof(IDTDesc);
    kidtr.base = IDTBASE;
    
    memcpy((void *) kidtr.base, (void *) kidt, kidtr.limit);
    
    asm("lidtl (_kidtr)");
}
