#include "stdlib.h"

void *heap_start = (void *) 0x200000;

void *malloc(unsigned long size)
{
    unsigned long realsize;
    unsigned long i;
    MallocHeader *block, *newblock;
    
    realsize = size + sizeof(MallocHeader);
    if ((i = realsize % MALLOC_MINSIZE))
    {
        realsize = realsize - i + MALLOC_MINSIZE;
    }
    
    block = (MallocHeader *) heap_start;
    
    while (block->used || block->size < realsize)
    {
        block = (MallocHeader *) ((char *) block + block->size);
    }
    
    if (block->size - realsize < MALLOC_MINSIZE)
    {
        block->used = 1;
    }
    else
    {
        newblock = (MallocHeader *) ((char *) block + realsize);
        newblock->size = block->size - realsize;
        newblock->used = 0;
        
        block->size = realsize;
        block->used = 1;
    }
    
    return (char *) block + sizeof(MallocHeader);
}

void free(void *addr)
{
    MallocHeader *block, *nextblock;
    
    block = (MallocHeader *) (addr - sizeof(MallocHeader));
    
    while ((nextblock = (MallocHeader *) ((char *) block + block->size))
            && !(nextblock->used))
    {
        block->size += nextblock->size;
    }
    
    block->used = 0;
}
