#include "pic.h"

void init_pic()
{
    // Init ICW1
    outb(0x20, 0x11);   // master
    outb(0xA0, 0x11);   // slave
    
    // Init ICW2
    outb(0x21, 0x20);   // master
    outb(0xA1, 0x70);   // slave

    // Init ICW3
    outb(0x21, 0x04);   // master
    outb(0xA1, 0x02);   // slave
    
    // Init ICW4
    outb(0x21, 0x01);   // master
    outb(0xA1, 0x01);   // slave
    
    // Interrupt mask
    outb(0x21, 0x0);    // master
    outb(0xA1, 0x0);    // slave
}
