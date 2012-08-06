
#ifndef hardware
#define hardware(descriptor) descriptor,
#endif

#define HARDWARE_COUNT 8

#ifdef HARDWARE_DESCRIPTORS             // Descriptors

hardware(&dcpu16_keyboard_hardware)     // 0x00
hardware(&dcpu16_screen_hardware)       // 0x01
hardware(0)                             // 0x02
hardware(0)                             // 0x03
hardware(0)                             // 0x04
hardware(0)                             // 0x05
hardware(0)                             // 0x06
hardware(0)                             // 0x07

#else                                   // Includes

#include "hardware/keyboard.h"
#include "hardware/dscreen.h"

#endif

#undef hardware
