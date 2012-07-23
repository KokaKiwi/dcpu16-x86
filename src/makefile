B                        := ../$(BUILDDIR)/
S                        := $Basm/

# New
SRCDIRS                  := lib core hardware

include_srcdir_csrc      = $(1)_CSRC     := $(wildcard $(1)/*.c)
include_srcdir_cobjs     = $(1)_COBJS    := $(addprefix $B,$(notdir $($(1)_CSRC:.c=$O)))
include_srcdir_casms     = $(1)_CASMS    := $(addprefix $S,$(notdir $($(1)_CSRC:.c=.asm)))
include_srcdir_asrc      = $(1)_ASRC     := $(wildcard $(1)/*.asm)
include_srcdir_aobjs     = $(1)_AOBJS    := $(addprefix $B,$(notdir $($(1)_ASRC:.asm=$O)))
include_srcdir_all       = ALL_OBJS      += $($(1)_COBJS) $($(1)_AOBJS)
include_srcdir_alla      = ALL_ASMS      += $($(1)_CASMS)

cobj_compile             = $(1) : $(2); $(CC) $(CCFLAGS) -o $(1) $(2)
aobj_compile             = $(1) : $(2); $(NASM) -f elf -o $(1) $(2)

casm_compile             = $(1) : $(2); $(CC) $(CAFLAGS) -o $(1) $(2)

compile_srcdir_c         = $(foreach cobj,$($(1)_COBJS),$(eval $(call cobj_compile,$(cobj),$(addprefix $(1)/,$(notdir $(cobj:$O=.c))))))
compile_srcdir_a         = $(foreach aobj,$($(1)_AOBJS),$(eval $(call aobj_compile,$(aobj),$(addprefix $(1)/,$(notdir $(aobj:$O=.asm))))))

generate_srcdir_c        = $(foreach casm,$($(1)_CASMS),$(eval $(call casm_compile,$(casm),$(addprefix $(1)/,$(notdir $(casm:.asm=.c))))))

$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_csrc,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_cobjs,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_casms,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_asrc,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_aobjs,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_all,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call include_srcdir_alla,$(srcdir))))

compile                  : $Bkernel

$Bkernel                 : $Bkernel.out ; $(OBJCOPY) -O binary $^ $@

$Bkernel.out             : $Bboot$O $Bkernel$O $Bprogram$O $(ALL_OBJS) ; $(LD) -T kernel.ld -s -o $@ $Bkernel$O $Bprogram$O $(ALL_OBJS)

$(foreach srcdir,$(SRCDIRS),$(eval $(call compile_srcdir_c,$(srcdir))))
$(foreach srcdir,$(SRCDIRS),$(eval $(call compile_srcdir_a,$(srcdir))))

$Bboot$O                 : boot.asm; $(NASM) -f elf -o $@ $^
$Bkernel$O               : kernel.c; $(CC) $(CCFLAGS) -o $@ $^
$Bprogram$O              : ../data/disk.bin ; $(OBJCOPY) -I binary -O elf32-i386 -B i386 --redefine-syms=../data/symbols.txt $^ $@

asm                      : $Skernel.asm $(ALL_ASMS)

$(foreach srcdir,$(SRCDIRS),$(eval $(call generate_srcdir_c,$(srcdir))))

$Skernel.asm             : kernel.c; $(CC) $(CCFLAGS) -S -o $@ $^
