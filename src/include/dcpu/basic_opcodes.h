#ifndef BASIC_OPCODES_H_
#define BASIC_OPCODES_H_

#include "../types.h"
#include "emulator.h"

extern uchar dcpu16_handle_opSET(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opADD(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSUB(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opMUL(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opMLI(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opDIV(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opDVI(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opMOD(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opMDI(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opAND(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opBOR(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opXOR(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSHR(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opASR(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSHL(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFB(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFC(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFE(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFN(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFG(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFA(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFL(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opIFU(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opADX(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSBX(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSTI(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);
extern uchar dcpu16_handle_opSTD(dcpu16_t *, uchar, uchar, dcpuw_t *, dcpuw_t *);

#endif
