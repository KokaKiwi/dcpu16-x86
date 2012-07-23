
#ifndef hardware
#define hardware(descriptor) descriptor,
#endif

#define HARDWARE_COUNT 8

#ifdef HARDWARE_DESCRIPTORS             // Descriptors

hardware(&debug_hardware)               // 0x00
hardware(0)                             // 0x01
hardware(0)                             // 0x02
hardware(0)                             // 0x03
hardware(0)                             // 0x04
hardware(0)                             // 0x05
hardware(0)                             // 0x06
hardware(0)                             // 0x07

#else                                   // Includes



#endif

#undef hardware
