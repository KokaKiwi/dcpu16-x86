#include "stdio.h"
#include "screen.h"
#include "io.h"
#include "color.h"

u8 screenX = 0;
u8 screenY = 17;
char mask = COLOR_WHITE | SURINTENSITY;

void scroll(unsigned int n)
{
    unsigned char *video, *tmp;
    
    for (video = (unsigned char *) RAMSCREEN;
            video < (unsigned char *) SCREENLIM; video += 2)
    {
        tmp = (unsigned char *) (video + n * 160);
        
        if (tmp < (unsigned char *) SCREENLIM)
        {
            *video = *tmp;
            *(video + 1) = *(tmp + 1);
        }
        else
        {
            *video = 0;
            *(video + 1) = 0x07;
        }
    }
    
    screenY -= n;
    if (screenY < 0)
    {
        screenY = 0;
    }
    
    show_cursor();
}

void clear_screen()
{
    unsigned char *video;
    
    for (video = (unsigned char *) RAMSCREEN;
            video < (unsigned char *) SCREENLIM; video += 2)
    {
        *video = 0;
        *(video + 1) = mask;
    }
}

void move_cursor(u8 x, u8 y)
{
    u16 c_pos = y * 80 + x;
    
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u8) c_pos);
    outb(0x3d4, 0x0e);
    outb(0x3d5, (u8) (c_pos >> 8));
}

void show_cursor()
{
    move_cursor(screenX, screenY);
}

void hide_cursor()
{
    move_cursor(-1, -1);
}
