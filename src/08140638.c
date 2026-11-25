/* Target 0x08140638, complete [0x08140638, 0x081409B2), 890 bytes,
 * 373 reachable instructions: a five-phase step that flips a twelve-frame
 * background animation between BG2 and BG3. */

#include "control_flags.h"

/* The ROM compares each incremented index unsigned (bhi/bls at 0x081407B0,
 * 0x08140778, 0x0814087C, 0x08140936, 0x08140960): the bounds are
 * sizeof-derived element counts. */
#define ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    void *destination;
} Display08140638;

typedef struct PaletteTransition PaletteTransition;

typedef struct {
    const void *map;
    s16 duration;
    u16 unknown_06;
} Frame08140638;

typedef struct {
    TransferRecord transfers[2];
    PaletteTransition *transition;
    PaletteTransition *fade;
    u8 count;
    u8 buffer;
    u8 frame;
    u8 unknown_43;
    s16 timer;
    u8 unknown_46[2];
    u16 phase;
    u16 depth;
    u16 stack[1];
} Screen08140638;

extern Display08140638 data_030008B0;
extern Display08140638 data_03000990;
extern const u16 data_08998B20[];
extern const u16 data_08998B40[];
extern const u8 data_08985324[];
extern const Frame08140638 data_083A932C[12];

extern void func_08000A98(TransferRecord *entry, const void *source,
                          void *destination, u16 count);
extern void func_08000B20(TransferRecord *entry, u16 first, void *second,
                          u16 count);
extern void func_08000BAC(TransferRecord *entry, const void *first,
                          void *second, u16 count, u16 field_10, u16 field_12,
                          u16 field_14);
extern PaletteTransition *func_08147D2C(u16 start, u16 count, u16 duration,
                                        const u16 *source);
extern PaletteTransition *func_08147AD0(u16 start, u16 count, u16 duration);
extern u32 func_081485D4(PaletteTransition *transition);
extern void *func_081484CC(PaletteTransition *transition);

u32 func_08140638(Screen08140638 *screen, u8 skip)
{
    if (screen->transition) {
        (*data_03000990.horizontal_offset)++;
        (*data_03000990.vertical_offset)++;
        (*data_030008B0.horizontal_offset)++;
        (*data_030008B0.vertical_offset)++;
        if (func_081485D4(screen->transition)) {
            func_081484CC(screen->transition);
            screen->transition = 0;
            switch (screen->count) {
            case 1:
                screen->transition = func_08147D2C(0x10, 0x10, 8, data_08998B20);
                break;
            case 2:
                screen->transition = func_08147AD0(0x10, 0x10, 0x10);
                break;
            }
            screen->count++;
        }
    }
    if (screen->fade && func_081485D4(screen->fade)) {
        func_081484CC(screen->fade);
        screen->fade = 0;
        screen->phase = 3;
    }
    if (skip && screen->fade == 0 && screen->transition == 0
        && screen->count == 0) {
        screen->count = 4;
        screen->fade = func_08147AD0(0, 0x100, 0x10);
    }

    switch (screen->phase) {
    case 0:
        *data_03000990.horizontal_offset = 0;
        *data_03000990.vertical_offset = 0;
        *data_030008B0.horizontal_offset = 0;
        *data_030008B0.vertical_offset = 0;
        func_08000A98(&screen->transfers[screen->buffer], data_08985324,
                      data_030008B0.tiles, 0x33A0);
        if (screen->buffer + 1 < ARRAY_COUNT(screen->transfers))
            screen->buffer++;
        else
            screen->buffer = 0;
        screen->phase = 1;
        break;
    case 1:
        if (screen->frame >= ARRAY_COUNT(data_083A932C)) {
            screen->phase = 3;
            break;
        }
        if (screen->frame && screen->frame + 1 >= ARRAY_COUNT(data_083A932C)
            && !skip) {
            screen->transition = func_08147D2C(0x10, 0x10, 8, data_08998B40);
            screen->count++;
        }
        /* Both arms end with the transfer and the BLDALPHA stores: the ROM
         * shares that tail (0x0814083E-0x08140860) and keeps the 0x03000940
         * base each arm loads into r4 (0x081407DA, 0x08140818) across the
         * call, while BLDCNT after the arms reloads it (0x08140862). */
        if (screen->buffer) {
            g_control_flags_03000940.bg2cnt = 0x1200;
            g_control_flags_03000940.bg3cnt = 0x1001;
            func_08000BAC(&screen->transfers[screen->buffer],
                          data_083A932C[screen->frame].map,
                          data_030008B0.destination, 0x1E, 0x14, 0x3C, 0x40);
            g_control_flags_03000940.bldalpha_lo = 8;
            g_control_flags_03000940.bldalpha_hi = 8;
        } else {
            g_control_flags_03000940.bg2cnt = 0x1201;
            g_control_flags_03000940.bg3cnt = 0x1000;
            func_08000BAC(&screen->transfers[screen->buffer],
                          data_083A932C[screen->frame].map,
                          data_03000990.destination, 0x1E, 0x14, 0x3C, 0x40);
            g_control_flags_03000940.bldalpha_lo = 8;
            g_control_flags_03000940.bldalpha_hi = 8;
        }
        g_control_flags_03000940.bldcnt_lo = 0x4C;
        g_control_flags_03000940.bldcnt_hi = 0x30;
        if (screen->buffer + 1 < ARRAY_COUNT(screen->transfers))
            screen->buffer++;
        else
            screen->buffer = 0;
        screen->timer = 0;
        screen->stack[screen->depth++] = screen->phase;
        screen->phase = 2;
        break;
    case 2:
        if (screen->timer < data_083A932C[screen->frame].duration) {
            screen->timer++;
            break;
        }
        screen->frame++;
        screen->phase = screen->stack[--screen->depth];
        break;
    case 3:
        if (screen->transition == 0 && screen->count > 2) {
            func_08000B20(&screen->transfers[screen->buffer], 0,
                          data_03000990.destination, 0x400);
            if (screen->buffer + 1 < ARRAY_COUNT(screen->transfers))
                screen->buffer++;
            else
                screen->buffer = 0;
            func_08000B20(&screen->transfers[screen->buffer], 0,
                          data_030008B0.destination, 0x400);
            if (screen->buffer + 1 < ARRAY_COUNT(screen->transfers))
                screen->buffer++;
            else
                screen->buffer = 0;
            screen->phase = 4;
        }
        break;
    case 4:
        if (screen->transition == 0 && screen->count > 2
            && screen->fade == 0) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.bldcnt_hi = 0;
            return 0;
        }
        break;
    }
    return 1;
}
