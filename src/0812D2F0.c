#include "ffta.h"

/* 0x0812D2F0..0x0812D356: 102 bytes, 49 reachable instructions. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} Object;

extern s32 func_0812D1DC(const Object *, const Object *, s8, s8,
                         s8, s8, s8, s32);
extern u8 func_08133A58(const Object *, s32);

s32 func_0812D2F0(const Object *source, const Object *target, s32 kind)
{
    s32 result;
    u8 valid;

    if (!func_0812D1DC(source, target, (s8)source->x, (s8)source->y,
                       (s8)target->x, (s8)target->y,
                       (s8)target->direction, kind))
        return 0;
    valid = func_08133A58(target, kind);
    result = 100;
    if (!valid)
        result = 0;
    return result;
}
