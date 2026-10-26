#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputState;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
} SystemState;

extern InputState data_02015738;
extern SystemState data_030028A0;
extern s32 func_08004D68(void);
extern u8 func_080C5F94(void *context);

static inline u8 input_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }
    if (((data_02015738.flags & 0x20) || data_02015738.count > 13) &&
        (data_030028A0.busy != 0 ||
         (data_030028A0.mode != 3 && data_030028A0.ticks > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

u8 func_080C73D8(void *context)
{
    u8 result;

    if (!input_blocked())
        result = func_080C5F94(context);
    else
        result = 2;
    return result;
}
