#include "ffta.h"

/* 0x0812DA0C..0x0812DAB6: 170 bytes, 76 reachable instructions. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} Object;

extern const u8 data_083A8472[];
extern const u8 data_083A844C[];
extern u8 func_0812D424(const Object *, const u8 *, u32);
extern s32 func_0812D1DC(const Object *, const Object *, s8, s8,
                         s8, s8, s8, s32);
extern u8 func_080CD50C(const Object *);
extern s32 func_0812C8DC(const Object *, const Object *, u32, u32);

s32 func_0812DA0C(const Object *source, const Object *target, s32 kind)
{
    s32 valid;
    s32 result;

    switch (kind) {
    case 0x31:
        if (!func_0812D424(target, data_083A8472, 3))
            return 0;
        break;
    case 0x41:
    case 0x42:
        if (!func_0812D424(target, data_083A844C, 19))
            return 0;
        break;
    }
    valid = func_0812D1DC(source, target, (s8)source->x, (s8)source->y,
                           (s8)target->x, (s8)target->y,
                           (s8)target->direction, kind);
    if (func_080CD50C(target) == 9 || valid == 0)
        return 0;
    result = func_0812C8DC(source, target, 2, 0);
    if (result <= 99)
        result >>= 1;
    return result;
}
