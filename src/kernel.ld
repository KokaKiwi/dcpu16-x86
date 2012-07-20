
STARTUP(../target/boot.o)
ENTRY(_start)
OUTPUT_ARCH("i386")

SECTIONS
{
    .text : {
        ../target/boot.o (.text)
    }
    
    .text (0x1000) : {
        * (.text)
    }
    
    .data : ALIGN(0x1000) {
        * (.data)
    }
    
    .bss : ALIGN(0x1000) {
        * (.bss)
    }
}
