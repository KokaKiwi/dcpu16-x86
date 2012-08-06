#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "types.h"

extern uchar keymap[];

extern void (*keyhandler)(uchar, uchar);

#endif
