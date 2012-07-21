#ifndef KEYMAP_H_
#define KEYMAP_H_

#include "types.h"

#define __KEYMAP_AZERTY__

#if defined(__KEYMAP_QWERTY__)
#include "keymap/qwerty.h"
#elif defined(__KEYMAP_AZERTY__)
#include "keymap/azerty.h"
#endif

#endif
