#ifndef STDLIB_H_
#define STDLIB_H_

#define MALLOC_MINSIZE  16

typedef struct malloc_header MallocHeader;
struct malloc_header
{
        unsigned long size:31;
        unsigned long used:1;
};

extern void *malloc(unsigned long);
extern void free(void *);

extern void *heap_start;

#endif
