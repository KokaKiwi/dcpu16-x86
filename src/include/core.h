#ifndef CORE_H_
#define CORE_H_

#include "types.h"
#include "dcpu/emulator.h"

extern void kernel(void);
extern void dcpu16_loadhardware(dcpu16_t *);
extern void dcpu16_tickhardware(dcpu16_t *);

extern uchar dcpu16_running;

#endif
