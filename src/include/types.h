#ifndef _I386_TYPE_
#define _I386_TYPE_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned char uchar;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#ifndef SIZE_T_
#define SIZE_T_
typedef u32 size_t;
#endif

#endif
