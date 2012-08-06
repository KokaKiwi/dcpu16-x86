#ifndef STDIO_H_
#define STDIO_H_

#include "types.h"
#include "stdarg.h"
#include "screen.h"

extern void putchar(char);
extern void print(const char *);
extern void printf(const char*, ...);
extern void println(const char*);
extern int  sprintf(char*, const char*, ...);

extern void std_keyhandler(uchar, uchar);
extern uchar getchar(void);

#endif
