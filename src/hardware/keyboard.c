#include "dcpu/emulator.h"
#include "dcpu/keymap.h"
#include "dcpu/hardware/keyboard.h"

#define __KEYMAP_AZERTY__

dcpuw_t dcpu16_keybuffer[256] = { 0 };
u8 dcpu16_keyindex = 0;

dcpuw_t dcpu16_keystate[0x92] = { 0 };

dcpuw_t dcpu16_keyboard_intmsg = 0;

dcpu16_t *dcpu16_keyboard_linkedcpu = 0;

int dcpu16_keyboard_interrupt(dcpu16_t *cpu, dcpu16_hardware_t *keyboard)
{
    dcpuw_t a, b, c;
    
    a = cpu->registers[DCPU16_REG_A];
    b = cpu->registers[DCPU16_REG_B];
    c = cpu->registers[DCPU16_REG_C];
    
    switch (a)
    {
        case 0:
            dcpu16_keyindex = 0;
            break;
            
        case 1:
            if (dcpu16_keyindex)
            {
                c = dcpu16_keybuffer[--dcpu16_keyindex];
            }
            else
            {
                c = 0;
            }
            break;
            
        case 2:
            c = dcpu16_keystate[b];
            break;
            
        case 3:
            dcpu16_keyboard_intmsg = b;
            break;
    }
    
    cpu->registers[DCPU16_REG_A] = a;
    cpu->registers[DCPU16_REG_B] = b;
    cpu->registers[DCPU16_REG_C] = c;
    
    return 0;
}

void dcpu16_keyboard_init(dcpu16_t *cpu, dcpu16_hardware_t *keyboard)
{
    dcpu16_keyboard_linkedcpu = cpu;
}

void dcpu16_keyboard_keyhandler(uchar c)
{
    dcpuw_t code = dcpu16_keyboard_keyconvert(c);
    
    if (code)
    {
        if (c < 0x80)
        {
            dcpu16_keybuffer[dcpu16_keyindex++] = code;
            dcpu16_keystate[code] = 1;
        }
        else
        {
            dcpu16_keystate[code] = 0;
        }
    }
    
    if (dcpu16_keyboard_intmsg && dcpu16_keyboard_linkedcpu)
    {
        dcpu16_interrupt(dcpu16_keyboard_linkedcpu, dcpu16_keyboard_intmsg, 0);
    }
}

dcpuw_t dcpu16_keyboard_keyconvert(uchar c)
{
    dcpuw_t code = 0;
    uchar ch;
    
    ch = c;
    
    if (ch >= 0x80)
    {
        ch -= 0x80;
    }
    
    code = dcpu16_keymap[ch];
    
    return code;
}

dcpu16_hardware_descriptor_t dcpu16_keyboard_hardware = { 0x30cf7406, 0x0001,
        0x12345678, dcpu16_keyboard_init, dcpu16_keyboard_interrupt, 0 };
