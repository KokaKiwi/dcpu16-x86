#ifndef STRING_H_
#define STRING_H_

#include "types.h"

#define FAST_STRCMP(x, y)  (*(x) != *(y) ? ((unsigned char) *(x) - (unsigned char) *(y)) : strcmp((x), (y)))

extern void *memcpy(void *, const void *, size_t);
extern void *memset(void *, unsigned, size_t);
extern int memcmp(const void *, const void *, size_t);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, size_t);
extern size_t strlen(const char *);
extern int strcmp(const char *, const char *);

#endif
