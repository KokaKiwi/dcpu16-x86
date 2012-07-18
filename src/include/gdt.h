#ifndef GDT_H_
#define GDT_H_

#include "types.h"

#define GDTBASE 0x0     // GDT address
#define GDTSIZE 0xff    // Size of GDT
typedef struct gdtdesc GDTDesc;
struct gdtdesc
{
    u16 limit_0_15;
    u16 base_0_15;
    u8 base_16_23;
    u8 access;
    u8 limit_16_19 :4;
    u8 other :4;
    u8 base_24_31;
}__attribute__ ((packed));

typedef struct gdtr GDTR;
struct gdtr
{
    u16 limit;
    u32 base;
}__attribute__ ((packed));

extern void init_gdt_desc(u32, u32, u8, u8, GDTDesc *);
extern void init_gdt(void);

extern GDTDesc kgdt[];
extern GDTR kgdtr;

#endif
