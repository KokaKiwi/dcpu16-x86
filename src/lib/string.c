#include "string.h"

void *memcpy(void *destination, const void *source, size_t num)
{
    while (num--)
    {
        *((char *) destination) = *((char *) source);
    }
    
    return destination;
}

void *memset(void *ptr, unsigned value, size_t num)
{
    while (num--)
    {
        *((unsigned *) ptr++) = value;
    }
    
    return ptr;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const char *p1 = ptr1;
    const char *p2 = ptr2;
    
    while (num-- && (*p1++ == *p2++))
        ;
    
    return (*(unsigned char *) --p1 < *(unsigned char *) --p2) ?
            -1 : (*(unsigned char *) p1 != *(unsigned char *) p2);
}

char *strcpy(char *destination, const char *source)
{
    while ((*destination++ = *source++))
        ;
    
    return destination;
}

char *strncpy(char *destination, const char *source, size_t num)
{
    while (num--)
    {
        *destination++ = *source++;
    }
    
    return destination;
}

size_t strlen(const char *str)
{
    size_t i;
    while (*str++)
    {
        i++;
    }
    
    return i;
}

int strcmp(const char* s1, const char* s2)
{
    while ((*s1++ == *s2++) && (*s1 != '\n') && *s1)
        ;
    return (*(unsigned char *) --s1 < *(unsigned char *) --s2) ?
            -1 : (*(unsigned char *) s1 != *(unsigned char *) s2);
}
