#ifndef SPECIAL_OPCODES_H_
#define SPECIAL_OPCODES_H_

#include "types.h"

extern uchar dcpu16_handle_opJSR(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opINT(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opIAG(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opIAS(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opRFI(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opIAQ(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opHWN(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opHWQ(dcpu16_t *, uchar, dcpuw_t *);
extern uchar dcpu16_handle_opHWI(dcpu16_t *, uchar, dcpuw_t *);

#endif
