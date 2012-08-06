#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../emulator.h"
#include "../../types.h"

extern int dcpu16_keyboard_interrupt(dcpu16_t *, dcpu16_hardware_t *);
extern void dcpu16_keyboard_keyhandler(uchar);
extern dcpuw_t dcpu16_keyboard_keyconvert(uchar);

extern dcpu16_hardware_descriptor_t dcpu16_keyboard_hardware;

#endif
