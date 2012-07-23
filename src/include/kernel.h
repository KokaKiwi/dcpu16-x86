#ifndef KERNEL_H_
#define KERNEL_H_

#include "types.h"
#include "dcpu/emulator.h"

extern dcpuw_t dcpu_program_start;
extern uchar dcpu_program_end;
extern unsigned long int dcpu_program_size;

extern void ok_msg(void);

#endif
