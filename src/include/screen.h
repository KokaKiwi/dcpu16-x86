#ifndef SCREEN_H_
#define SCREEN_H_

#include "types.h"

#define RAMSCREEN   0xB8000
#define SIZESCREEN  0xFA0
#define SCREENLIM   0xB8FA0

extern u8 screenX;
extern u8 screenY;
extern char mask;

// Text mode
extern void scroll(unsigned int);
extern void clear_screen(void);
extern void move_cursor(u8, u8);
extern void show_cursor(void);
extern void hide_cursor(void);

#endif
