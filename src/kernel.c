#include "types.h"
#include "boot.h"
#include "stdio.h"
#include "string.h"
#include "io.h"
#include "idt.h"
#include "core.h"
#include "gdt.h"
#include "pic.h"
#include "keyboard.h"
#include "screen.h"
#include "color.h"
#include "kernel.h"

unsigned dcpu_program_size;

void load_gdt(void);
void load_sp(void);
void load_pic(void);
void load_idt(void);

void _main(struct multiboot_info *mbi)
{
    clear_screen();
    screenX = 0;
    screenY = 0;
    hide_cursor();
    
    // Boot
    mask = COLOR_WHITE;
    
    println("Loading DCPU-16 for x86 [0.1.0] ...");
    // printf("Memory: %d (low), %d (high)\n", mbi->low_mem, mbi->high_mem);
    
    load_gdt();
    load_sp();
    load_idt();
    load_pic();
    // Load vars
    // + Get DCPU Program size
    dcpu_program_size = dcpu_program_end - dcpu_program;
    // Load default key handler
    keyhandler = &std_keyhandler;
    
    sti;
    show_cursor();
    
    kernel();
    
    while(1);
}

void ok_msg()
{
    screenX = 40;
    mask = COLOR_GREEN | SURINTENSITY;
    println("OK");
    mask = COLOR_WHITE;
}

void load_gdt()
{
    print("Initializing GDT...");
    init_gdt();
    ok_msg();
}

void load_sp()
{
    print("Initializing stack pointer...");
    asm("movw $0x18, %ax \n \
             movw %ax, %ss   \n \
             movl $0x20000, %esp");
    ok_msg();
}

void load_pic()
{
    print("Initializing PIC...");
    init_pic();
    ok_msg();
}

void load_idt()
{
    print("Initializing interrupts...");
    init_idt();
    ok_msg();
}
