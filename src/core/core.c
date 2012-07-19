#include "kernel.h"
#include "stdio.h"
#include "stdarg.h"
#include "emulator.h"
#include "core.h"

void kernel()
{
    unsigned long int ksize = 1256000;
    
    printf("%x - %x - %x - %x - %x", ksize, ksize, ksize, ksize, ksize);
}
