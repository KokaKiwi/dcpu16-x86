#ifndef IDT_H_
#define IDT_H_

#include "types.h"

#define IDTBASE     0x0800
#define IDTSIZE     0xff

#define INTGATE     0x8e00
#define TRAPGATE     0xef00

typedef struct idtdesc IDTDesc;
struct idtdesc
{
    u16 offset_0_15;
    u16 select;
    u16 type;
    u16 offset_16_31;
}__attribute__((packed));

typedef struct idtr IDTR;
struct idtr
{
    u16 limit;
    u32 base;
}__attribute__((packed));

extern void init_idt_desc(u16, u32, u16, IDTDesc *);
extern void init_idt(void);

extern void asm_default_int(void);
extern void asm_exec_GP(void);
extern void asm_exec_PF(void);
extern void asm_irq_0(void);
extern void asm_irq_1(void);

extern IDTR kidtr;
extern IDTDesc kidt[];

#endif
