global _dcpu_program, _dcpu_program_end

_dcpu_program:
    incbin "../data/disk.bin"
    db 0
_dcpu_program_end:
