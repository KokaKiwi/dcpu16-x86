NASM=/usr/sbin/nasm
BOCHS=/usr/fbin/bochs
CC=cc
CCFLAGS=-c
OBJCOPY=objcopy
LD=ld
O=.o
BUILDDIR=../target
B=$(BUILDDIR)/

compile: $Bbootsect

# Bootsect
$Bbootsect: bootsect.asm; $(NASM) -f bin -o $@ $^