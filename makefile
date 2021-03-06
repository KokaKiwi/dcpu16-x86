export BOCHS	:= /usr/fbin/bochs
export NASM		:= nasm
export CC		:= gcc
export INCDIRS  := include
export CFLAGS   := -O3 -Os -nostartfiles -fno-builtin $(foreach incdir,$(INCDIRS),$(addprefix -I,$(incdir)))
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
run 			: bochs

# Compile
# + Bootsect
bootsect:
	mkdir -p $(BUILDDIR)
	make -C boot

# + Kernel
kernel		:
	make -C src compile

asm			:
	mkdir -p $S
	make -C src asm

# + Floppy
floppy			: floppyA

floppyA			: $(OBJS) ; cat $(OBJS) /dev/zero | dd of=floppyA bs=512 count=2880

# Bochs
bochs			:
	$(BOCHS) -f bochsrc.bxrc
	
# Clean
clean			:
	rm -f $(wildcard $B*.*)
	rm -f $(wildcard $S*)