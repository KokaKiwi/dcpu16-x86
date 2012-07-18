#include "string.h"
#include "gdt.h"

GDTDesc kgdt[GDTSIZE];
GDTR kgdtr;

void init_gdt_desc(u32 base, u32 limit, u8 access, u8 other, GDTDesc *desc)
{
    desc->limit_0_15 = (limit & 0xffff);
    desc->limit_16_19 = (limit & 0xf0000) >> 16;
    
    desc->base_0_15 = (base & 0xffff);
    desc->base_16_23 = (base & 0xff0000) >> 16;
    desc->base_24_31 = (base & 0xff000000) >> 24;
    
    desc->access = access;
    desc->other = (other & 0xf);
    return;
}

void init_gdt()
{
    // Init segment descriptors
    init_gdt_desc(0x0, 0x0,     0x0,  0x0,  &kgdt[0]);      // NULL
    init_gdt_desc(0x0, 0xfffff, 0x9b, 0x0d, &kgdt[1]);      // Code
    init_gdt_desc(0x0, 0xfffff, 0x93, 0x0d, &kgdt[2]);      // Data
    init_gdt_desc(0x0, 0x0,     0x97, 0x0d, &kgdt[3]);      // Stack
    
    kgdtr.limit = GDTSIZE * sizeof(GDTDesc);
    kgdtr.base = GDTBASE;
    
    memcpy((void *) kgdtr.base, (void *) kgdt, kgdtr.limit);
    
    asm("lgdtl (_kgdtr)");
    
    asm("   movw $0x10, %ax     \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            ljmp $0x08, $next   \n \
            next:               \n");
}
