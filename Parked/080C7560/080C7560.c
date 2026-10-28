#include "ffta.h"

/* 0x080C7560..0x080C75F2: 146 bytes, 66 instructions, including pools. */
typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputGate;

typedef struct {
    u8 unknown_00[2];
    u8 type;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 count;
} MenuGate;

extern InputGate data_02015738;
extern MenuGate data_030028A0;
extern u32 func_08004D68(void);
extern u8 func_080C69C8(void *context);

static inline u8 input_is_blocked(const InputGate *gate)
{
    if (gate->flags & 0x40) {
        if (gate->flags & 0x80) {
            return func_08004D68() != 1;
        }
        return 0;
    }
    if ((gate->flags & 0x20) || gate->count > 13) {
        const MenuGate *menu = &data_030028A0;
        if (menu->busy || (menu->type != 3 && menu->count > 16)) {
            return 1;
        }
    }
    if (gate->flags & 8) {
        return 1;
    }
    return 0;
}

u32 func_080C7560(void *context)
{
    if (input_is_blocked(&data_02015738)) {
        return 2;
    }
    return func_080C69C8(context);
}
