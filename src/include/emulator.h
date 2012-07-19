#ifndef EMULATOR_H_
#define EMULATOR_H_

#include "types.h"

typedef unsigned short dcpuw_t;
typedef signed short dcpusw_t;

/* AB VALUES */
#define DCPU16_AB_VALUE_REG_A               0x00
#define DCPU16_AB_VALUE_REG_B               0x01
#define DCPU16_AB_VALUE_REG_C               0x02
#define DCPU16_AB_VALUE_REG_X               0x03
#define DCPU16_AB_VALUE_REG_Y               0x04
#define DCPU16_AB_VALUE_REG_Z               0x05
#define DCPU16_AB_VALUE_REG_I               0x06
#define DCPU16_AB_VALUE_REG_J               0x07
#define DCPU16_AB_VALUE_PTR_REG_A           0x08
#define DCPU16_AB_VALUE_PTR_REG_B           0x09
#define DCPU16_AB_VALUE_PTR_REG_C           0x0A
#define DCPU16_AB_VALUE_PTR_REG_X           0x0B
#define DCPU16_AB_VALUE_PTR_REG_Y           0x0C
#define DCPU16_AB_VALUE_PTR_REG_Z           0x0D
#define DCPU16_AB_VALUE_PTR_REG_I           0x0E
#define DCPU16_AB_VALUE_PTR_REG_J           0x0F
#define DCPU16_AB_VALUE_PTR_REG_A_PLUS_WORD 0x10
#define DCPU16_AB_VALUE_PTR_REG_B_PLUS_WORD 0x11
#define DCPU16_AB_VALUE_PTR_REG_C_PLUS_WORD 0x12
#define DCPU16_AB_VALUE_PTR_REG_X_PLUS_WORD 0x13
#define DCPU16_AB_VALUE_PTR_REG_Y_PLUS_WORD 0x14
#define DCPU16_AB_VALUE_PTR_REG_Z_PLUS_WORD 0x15
#define DCPU16_AB_VALUE_PTR_REG_I_PLUS_WORD 0x16
#define DCPU16_AB_VALUE_PTR_REG_J_PLUS_WORD 0x17
#define DCPU16_AB_VALUE_PUSH_OR_POP         0x18
#define DCPU16_AB_VALUE_PEEK                0x19
#define DCPU16_AB_VALUE_PICK                0x1A
#define DCPU16_AB_VALUE_REG_SP              0x1B
#define DCPU16_AB_VALUE_REG_PC              0x1C
#define DCPU16_AB_VALUE_REG_EX              0x1D
#define DCPU16_AB_VALUE_PTR_WORD            0x1E
#define DCPU16_AB_VALUE_WORD                0x1F

/* REGISTERS */
#define DCPU16_REGISTER_COUNT               12
#define DCPU16_REG_A                        0x0
#define DCPU16_REG_B                        0x1
#define DCPU16_REG_C                        0x2
#define DCPU16_REG_X                        0x3
#define DCPU16_REG_Y                        0x4
#define DCPU16_REG_Z                        0x5
#define DCPU16_REG_I                        0x6
#define DCPU16_REG_J                        0x7
#define DCPU16_REG_PC                       0x8
#define DCPU16_REG_SP                       0x9
#define DCPU16_REG_EX                       0xa
#define DCPU16_REG_IA                       0xb

#define DCPU16_RAM_SIZE                     0x10000
#define DCPU16_HARDWARE_SLOTS               65535
#define DCPU16_MAX_INTERRUPT_QUEUE_LENGTH   256

typedef struct _dcpu16_hardware_t dcpu16_hardware_t;
typedef struct _dcpu16_queued_interrupt_t dcpu16_queued_interrupt_t;
typedef struct _dcpu16_interrupt_queue dcpu16_interrupt_queue;
typedef struct _dcpu16_register_listener dcpu16_register_listener;
typedef struct _dcpu16_ram_listener dcpu16_ram_listener;
typedef struct _dcpu16_t dcpu16_t;

typedef uchar (*basic_opcode_handler)(dcpu16_t *, dcpuw_t, dcpuw_t, dcpuw_t *,
        dcpuw_t *);
typedef uchar (*special_opcode_handler)(dcpu16_t *, dcpuw_t, dcpuw_t *);

struct _dcpu16_hardware_t
{
    uchar present;
    unsigned int id;
    unsigned short version;
    unsigned int manufacturer;
    int (*interrupt)(dcpu16_t *, dcpu16_hardware_t *);
    void *custom;
};

struct _dcpu16_queued_interrupt_t
{
    dcpuw_t message;
    dcpu16_queued_interrupt_t *next, *prev;
};

struct _dcpu16_interrupt_queue
{
    dcpu16_queued_interrupt_t root;
    unsigned short size;
};

struct _dcpu16_register_listener
{
    void (*callback)(uchar, dcpuw_t);
    dcpu16_register_listener *next, *prev;
};

struct _dcpu16_ram_listener
{
    void (*callback)(dcpuw_t, dcpuw_t);
    dcpu16_ram_listener *next, *prev;
};

struct _dcpu16_t
{
    struct
    {
        uchar enabled;
        double sample_time;
        double sample_frequency;
        double sample_start_time;
        unsigned intruction_count;
    } profiling;
    
    struct
    {
        dcpu16_register_listener *register_listener;
        dcpu16_ram_listener *ram_listener;
    } listeners;
    
    dcpuw_t registers[DCPU16_REGISTER_COUNT];
    dcpuw_t ram[DCPU16_RAM_SIZE];
    dcpu16_hardware_t hardware[DCPU16_HARDWARE_SLOTS];
    
    dcpu16_interrupt_queue interrupt_queue;
    uchar interrupts_enabled;
}__attribute__((packed));

extern void dcpu16_set(dcpu16_t *, dcpuw_t *, dcpuw_t);
extern dcpuw_t *dcpu16_register_pointer(dcpu16_t *, uchar);
extern uchar dcpu16_get_pointer(dcpu16_t *, uchar, dcpuw_t *, dcpuw_t **, uchar);

extern void dcpu16_call_ram_listeners(dcpu16_t *, dcpuw_t, dcpuw_t);
extern void dcpu16_call_register_listeners(dcpu16_t *, uchar, dcpuw_t);

extern void dcpu16_init(dcpu16_t *);
extern unsigned char dcpu16_step(dcpu16_t *);
extern void dcpu16_skip_next_instruction(dcpu16_t *);
extern void dcpu16_trigger_interrupt(dcpu16_t *);

#endif
