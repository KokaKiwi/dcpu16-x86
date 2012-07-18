%define BASE  0x100
%define KSIZE 50         ; Nombre de secteurs à charger

[BITS 16]
[ORG 0x0]

jmp start

%include "gdt.asm"

start:
; Initialisation des segments
	mov ax, 0x07c0
	mov ds, ax
	mov es, ax
; On place la pile en [0x8f000;0x80000]
	mov ax, 0x8000
	mov ss, ax
	mov sp, 0xf000
; Recuperation de l'unité de boot
    mov [bootdrv], dl
    
; Chargement du noyau en mémoire
    xor ax, ax
    int 0x13
    
    push es
    mov ax, BASE
    mov es, ax
    mov bx, 0

    mov ah, 2
    mov al, KSIZE
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [bootdrv]
    int 0x13
    pop es

; Initialisation du GDT
; 0- Définition du GDT
    descInit 0, 0xFFFFF, 10011011b, 1101b, gdt_cs
    descInit 0, 0xFFFFF, 10010011b, 1101b, gdt_ds
; 1- Calcul de la limite du GDT
    mov ax, gdtend
    mov bx, gdt
    sub ax, bx
    mov word [gdtptr], ax
; 2- Calcul de la base du GDT
    xor eax, eax
    xor ebx, ebx
    mov ax, ds
    mov ecx, eax
    shl ecx, 4
    mov bx, gdt
    add ecx, ebx
    mov dword [gdtptr+2], ecx

; Passage en mode protégé
    cli             ; Desactive les int
    lgdt [gdtptr]
    mov eax, cr0
    or ax, 1
    mov cr0, eax    ; PE = 1 (CR0)

    jmp next
next:
; Initialisation des segments
; 1- Segment de données
    mov ax, 0x10
    mov ds, ax
    mov fs, ax
    mov gs, ax
    mov es, ax
; 2- Segment de pile
    mov ss, ax
    mov esp, 0x9f000
    
; Passage au noyau
    jmp dword 0x8:0x1000

end: jmp end

; Variables
bootdrv: db 0

; GDT
gdt:
gdt_null:
    dw 0, 0, 0, 0   ; Descripteur NULL
gdt_cs:
    dw 0, 0, 0, 0   ; Descripteur CS (Code Segment)
gdt_ds:
    dw 0, 0, 0, 0   ; Descripteur DS (Data Segment)
gdtend:

; GDT Pointer
gdtptr:
    dw 0x0000       ; Limite
    dd 0            ; Base

; On remplit le reste
times 510-($-$$) db 144
dw 0xAA55
