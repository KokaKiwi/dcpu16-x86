#ifndef KERNEL_H_
#define KERNEL_H_

#include "types.h"

extern uchar dcpu_program_start;
extern uchar dcpu_program_end;
extern unsigned long dcpu_program_size;

extern void ok_msg(void);

#endif
