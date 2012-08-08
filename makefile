export BOCHS	:= /usr/fbin/bochs/bochs
export QEMU     := /usr/fbin/qemu
export NASM		:= nasm
export CC		:= gcc
export INCDIRS  := include
export CFLAGS   := -O3 -Os -nostartfiles -fno-builtin -fno-leading-underscore -m32 $(foreach incdir,$(INCDIRS),$(addprefix -I,$(incdir)))
export CCFLAGS	:= -c -g $(CFLAGS)
export CAFLAGS	:= -S $(CFLAGS)
export OBJCOPY	:= objcopy
export LD		:= ld
export LDFLAGS	:= -g

export BUILDDIR	:= target

export O		:= .o
B				:= $(BUILDDIR)/
S				:= $Basm/

OBJS			:= $Bbootsect $Bkernel

compile			: bootsect kernel floppy

# Compile
# + Bootsect
bootsect:
	mkdir -p $(BUILDDIR)
	make -C boot

# + Kernel
libs            := $(wildcard src/libs/*.tar)

untar_lib       := tar -xf $(1) -C src/libs/

kernel		:
	$(foreach lib,$(libs),tar -xf $(lib) -C src/libs/)
	make -C src compile
	rm -f src/libs/*.c
	rm -f src/libs/*.asm

asm			:
	mkdir -p $S
	make -C src asm

# + Floppy
floppy			: floppyA

floppyA			: $(OBJS) ; cat $(OBJS) /dev/zero | dd of=floppyA bs=512 count=2880

# QEmu
run-qemu		:
	$(QEMU)/qemu-system-i386 -fda floppyA
# Bochs
run-bochs		:
	$(BOCHS) -f bochsrc.bxrc
	
# Clean
clean			:
	rm -f $(wildcard $B*.*)
	rm -f $(wildcard $S*)