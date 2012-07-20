#ifndef ENDIAN_H_
#define ENDIAN_H_

#include "types.h"

#define IS_LITTLE_ENDIAN (*(u16*)"\0\1">>8)
#define IS_BIG_ENDIAN (*(u16*)"\1\0">>8)

#endif
