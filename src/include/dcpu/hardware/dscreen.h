#ifndef DSCREEN_H_
#define DSCREEN_H_

#include "../../types.h"
#include "../emulator.h"

#define BORDER_SIZE                     3

#define DCPU16_SCREEN_FONT_WIDTH        4
#define DCPU16_SCREEN_FONT_HEIGHT       8

#define DCPU16_SCREEN_SLOTS_WIDTH       32
#define DCPU16_SCREEN_SLOTS_HEIGHT      12

#define DCPU16_SCREEN_CONTENT_WIDTH     (DCPU16_SCREEN_SLOTS_WIDTH * DCPU16_SCREEN_FONT_WIDTH)
#define DCPU16_SCREEN_CONTENT_HEIGHT    (DCPU16_SCREEN_SLOTS_HEIGHT * DCPU16_SCREEN_FONT_HEIGHT)

#define DCPU16_SCREEN_WIDTH             (DCPU16_SCREEN_CONTENT_WIDTH + BORDER_SIZE * 2)
#define DCPU16_SCREEN_HEIGHT            (DCPU16_SCREEN_CONTENT_HEIGHT + BORDER_SIZE * 2)

#define DCPU16_SCREEN_LENGTH            (DCPU16_SCREEN_WIDTH * DCPU16_SCREEN_HEIGHT)

extern dcpuw_t dcpu16_screen[DCPU16_SCREEN_LENGTH];

extern dcpu16_hardware_descriptor_t dcpu16_screen_hardware;

#endif
