#include "stdio.h"

void putchar(char c)
{
    char *vram = (char *) (RAMSCREEN + 2 * screenX + 160 * screenY);
    switch (c)
    {
        case '\n':
            screenX = 0;
            screenY++;
            break;
        case 9:
            screenX = screenX + 8 - (screenX % 8);
            break;
        case 13:
            screenX = 0;
            break;
        default:
            *vram = c;
            *(vram + 1) = mask;
            
            screenX++;
            if (screenX > 79)
            {
                screenX = 0;
                screenY++;
            }
            break;
    }
}

void printf_putu(unsigned d, unsigned int radix)
{
    static char buf[16] = { 0 };
    unsigned i = 0, index = 0;
    
    if (d)
    {
        while (d)
        {
            index = (unsigned) (d % radix);
            d /= radix;
            
            buf[i++] = "0123456789abcdef"[index];
        }
        
        while (i--)
        {
            putchar(buf[i]);
        }
    }
    else
    {
        putchar('0');
    }
}

void printf_putd(int d, unsigned radix)
{
    if (d < 0)
    {
        putchar('-');
        d = -d;
    }
    
    printf_putu(d, radix);
}

void printf(const char *format, ...)
{
    va_list args;
    char c = 0;
    
    va_start(args, format);
    
    while ((c = *format++))
    {
        if (c == '%')
        {
            switch (*format++)
            {
                case 'd':
                    printf_putd(va_arg(args, int), 10);
                    break;
                case 'u':
                    printf_putu(va_arg(args, unsigned int), 10);
                    break;
                case 'l':
                    if (*format == 'd')
                    {
                        printf_putu(va_arg(args, unsigned long int), 10);
                        format++;
                    }
                    break;
                case 'x':
                    printf_putu(va_arg(args, unsigned int), 16);
                    break;
                case 'o':
                    printf_putu(va_arg(args, unsigned int), 8);
                    break;
                case 'b':
                    printf_putu(va_arg(args, unsigned int), 2);
                    break;
                case 's':
                    print(va_arg(args, char *));
                    break;
                case 'c':
                    putchar(va_arg(args, unsigned int));
                    break;
            }
        }
        else
        {
            putchar(c);
        }
    }

    va_end(args);
}

void print(const char *str)
{
    while (*str)
    {
        putchar(*str);
        str++;
    }
}

void println(const char *str)
{
    print(str);
    putchar('\n');
}

int sprintf(char *str, const char *format, ...)
{
    return 0;
}

uchar std_keybuffer[256];
unsigned std_bufpointer = 0;

void std_keyhandler(uchar c)
{
    if (std_bufpointer < 256)
    {
        std_keybuffer[std_bufpointer++] = c;
    }
}

uchar getchar()
{
    uchar c = 0;
    
    if (std_bufpointer > 0)
    {
        c = std_keybuffer[--std_bufpointer];
    }
    
    return c;
}
