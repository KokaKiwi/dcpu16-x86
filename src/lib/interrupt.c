#include "types.h"
#include "screen.h"
#include "stdio.h"
#include "io.h"
#include "keyboard.h"
#include "keymap.h"
#include "color.h"

void (*keyhandler)(uchar) = 0;

void isr_default_int()
{
    mask = COLOR_RED | BG_CYAN;
    println("default interrupt.");
}

void isr_GP_exec()
{
    mask = COLOR_RED | BG_CYAN;
    println("GP fault");
    show_cursor();
    asm("hlt");
}

void isr_PF_exec()
{
    u32 faulting_addr;
    u32 eip;
    
    asm("movl 60(%%ebp), %%eax; \
         mov %%eax, %0;         \
         mov %%cr2, %%eax;      \
         mov %%eax, %1": "=m"(eip), "=m"(faulting_addr): );
    
    mask = COLOR_RED | BG_CYAN;
    printf("PF on eip: 0x%x. cr2: 0x%x\n", eip, faulting_addr);
    
    asm("hlt");
}

void isr_clock_int()
{
    static unsigned tic = 0;
    static unsigned sec = 0;
    tic++;
    if (tic % 100 == 0)
    {
        sec++;
        tic = 0;
    }
}

void isr_keyboard_int()
{
    uchar i, c;
    unsigned index;
    static unsigned lshift;
    static unsigned rshift;
    static unsigned alt;
    static unsigned ctrl;
    
    do
    {
        i = inb(0x64);
    }
    while (!(i & 0x01));
    
    i = inb(0x60);
    i--;
    
    if (i < 0x80)    // Pressed key
    {
        switch (i)
        {
            case 0x1c:
                ctrl = 1;
                break;
            case 0x29:
                lshift = 1;
                break;
            case 0x35:
                rshift = 1;
                break;
            case 0x37:
                alt = 1;
                break;
            default:
                index = i * 4;
                if (lshift || rshift)
                {
                    index++;
                }
                else if (alt)
                {
                    index += 2;
                }
                c = keymap[index];
                if (keyhandler)
                {
                    keyhandler(c);
                }
                break;
        }
    }
    else            // Released key
    {
        i -= 0x80;
        switch (i)
        {
            case 0x1c:
                ctrl = 0;
                break;
            case 0x29:
                lshift = 0;
                break;
            case 0x35:
                rshift = 0;
                break;
            case 0x37:
                alt = 0;
                break;
        }
    }
    
    show_cursor();
}
