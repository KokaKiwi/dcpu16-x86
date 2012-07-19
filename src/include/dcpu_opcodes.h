/*
 * opcode(handler)
 * 
 * handler : Opcode handler
 */
#include "emulator.h"

#if defined(BASIC_OPCODES)      // Basic opcodes

opcode(0)                       // 0x00
opcode(dcpu16_handle_opSET)     // 0x01
opcode(dcpu16_handle_opADD)     // 0x02
opcode(dcpu16_handle_opSUB)     // 0x03
opcode(dcpu16_handle_opMUL)     // 0x04
opcode(dcpu16_handle_opMLI)     // 0x05
opcode(dcpu16_handle_opDIV)     // 0x06
opcode(dcpu16_handle_opDVI)     // 0x07
opcode(dcpu16_handle_opMOD)     // 0x08
opcode(dcpu16_handle_opMDI)     // 0x09
opcode(dcpu16_handle_opAND)     // 0x0a
opcode(dcpu16_handle_opBOR)     // 0x0b
opcode(dcpu16_handle_opXOR)     // 0x0c
opcode(dcpu16_handle_opSHR)     // 0x0d
opcode(dcpu16_handle_opASR)     // 0x0e
opcode(dcpu16_handle_opSHL)     // 0x0f
opcode(dcpu16_handle_opIFB)     // 0x10
opcode(dcpu16_handle_opIFC)     // 0x11
opcode(dcpu16_handle_opIFE)     // 0x12
opcode(dcpu16_handle_opIFN)     // 0x13
opcode(dcpu16_handle_opIFG)     // 0x14
opcode(dcpu16_handle_opIFA)     // 0x15
opcode(dcpu16_handle_opIFL)     // 0x16
opcode(dcpu16_handle_opIFU)     // 0x17
opcode(0)                       // 0x18
opcode(0)                       // 0x19
opcode(dcpu16_handle_opADX)     // 0x1a
opcode(dcpu16_handle_opSBX)     // 0x1b
opcode(0)                       // 0x1c
opcode(0)                       // 0x1d
opcode(dcpu16_handle_opSTI)     // 0x1e
opcode(dcpu16_handle_opSTD)     // 0x1f

#elif defined(SPECIAL_OPCODES)  // Special opcodes

opcode(0)                       // 0x00
opcode(dcpu16_handle_opJSR)     // 0x01
opcode(0)                       // 0x02
opcode(0)                       // 0x03
opcode(0)                       // 0x04
opcode(0)                       // 0x05
opcode(0)                       // 0x06
opcode(0)                       // 0x07
opcode(dcpu16_handle_opINT)     // 0x08
opcode(dcpu16_handle_opIAG)     // 0x09
opcode(dcpu16_handle_opIAS)     // 0x0a
opcode(dcpu16_handle_opRFI)     // 0x0b
opcode(dcpu16_handle_opIAQ)     // 0x0c
opcode(0)                       // 0x0d
opcode(0)                       // 0x0e
opcode(0)                       // 0x0f
opcode(dcpu16_handle_opHWN)     // 0x10
opcode(dcpu16_handle_opHWQ)     // 0x11
opcode(dcpu16_handle_opHWI)     // 0x12
opcode(0)                       // 0x13
opcode(0)                       // 0x14
opcode(0)                       // 0x15
opcode(0)                       // 0x16
opcode(0)                       // 0x17 
opcode(0)                       // 0x18
opcode(0)                       // 0x19
opcode(0)                       // 0x1a
opcode(0)                       // 0x1b
opcode(0)                       // 0x1c
opcode(0)                       // 0x1d
opcode(0)                       // 0x1e
opcode(0)                       // 0x1f

#else                           // Includes

#include "basic_opcodes.h"
#include "special_opcodes.h"

#endif
