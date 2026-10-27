#include "ffta.h"

/* 0x0813034C..0x081303AC: 96 bytes. */
typedef struct {
    u8 kind;
    u8 mode;
    u8 unknown_02;
    s8 offset;
} ValueInfo;

extern u8 func_080CDA4C(void *unit);
extern u32 func_080C7EA4(void *unit, u32 field);

static inline s32 magnitude(s32 value)
{
    if (value < 0)
        return -value;
    return value;
}

s16 func_0813034C(void *unit, s16 limit)
{
    ValueInfo *info;
    if (func_080CDA4C(unit))
        return 0;

    info = (ValueInfo *)func_080C7EA4(unit, 68);
    if (magnitude(info->offset) >= limit || info->kind == 2 || info->mode == 4)
        return 0;

    return func_080C7EA4(unit, 20) * (limit - magnitude(info->offset)) / 8;
}
