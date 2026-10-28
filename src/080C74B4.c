#include "ffta.h"

/* 0x080C74B4..0x080C7546: 146 bytes, including literal pools. */
typedef struct {
    u8 unknown_00[0xAC];
    u8 value;
    u8 unknown_AD;
    u8 flags;
} Status;

typedef struct {
    u8 unknown_00[2];
    u8 type;
    u8 unknown_03[0x11D];
    u16 active;
    u16 value;
} Control;

extern Status data_02015738;
extern Control data_030028A0;
extern s32 func_08004D68(void);
extern u8 func_080C6480(void *object);

static inline u8 is_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }

    if (((data_02015738.flags & 0x20) || data_02015738.value > 13) &&
        (data_030028A0.active != 0 ||
         (data_030028A0.type != 3 && data_030028A0.value > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

u8 func_080C74B4(void *object)
{
    if (is_blocked())
        return 2;
    return func_080C6480(object);
}
