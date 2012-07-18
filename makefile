export BOCHS	:= /usr/fbin/bochs
export NASM		:= nasm
export CC		:= gcc
export CCFLAGS	:= -c -g -nostartfiles -fno-builtin -Iinclude
export OBJCOPY	:= objcopy
export LD		:= ld
export LDFLAGS	:= -g

export BUILDDIR	:= target

export O		:= .o
B				:= $(BUILDDIR)/

OBJS			:= $Bbootsect $Bkernel

compile			: bootsect kernel floppy
run 			: bochs

# Compile
# + Bootsect
bootsect:
	make -C boot

# + Kernel
kernel		:
	make -C src

# + Floppy
floppy			: floppyA

floppyA			: $(OBJS) ; cat $(OBJS) /dev/zero | dd of=floppyA bs=512 count=2880

# Bochs
bochs			:
	$(BOCHS)
	
# Clean
clean			:
	rm -f $(wildcard $B*)