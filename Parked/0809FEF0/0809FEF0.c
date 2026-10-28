#include "ffta.h"

extern u8 func_0801CC7C(u8 x, u8 y);
extern u8 func_0801CD08(u8 x, u8 y);
extern u8 func_0812EE98(void *context, u16 identifier);
extern s16 func_0812E1A8(void *context, u8 source_x, u8 source_y,
                        u8 target_x, u8 target_y, u16 identifier, u32 mode);
extern u8 func_0812EED0(void *context, u16 identifier);

/* 0x0809FEF0..0x080A0012: 290 bytes, 140 instructions. */
u32 func_0809FEF0(void *context, s8 source_x, s8 source_y,
                  s8 target_x, s8 target_y, u16 identifier, u8 alternate)
{
    u8 flags;
    u16 type;
    s8 range;
    u8 eligible;
    s32 dx;
    s32 dy;

    if (!func_0801CC7C(target_x, target_y)) {
        return 0;
    }
    flags = func_0801CD08(target_x, target_y);
    if (flags & 1) {
        return 0;
    }
    if (flags & 8) {
        return 0;
    }
    if (source_x == target_x && source_y == target_y) {
        return 0;
    }
    type = func_0812EE98(context, identifier);
    if (type != 13 && type != 14 && type != 19) {
            s16 result = func_0812E1A8(context, source_x, source_y,
                                      target_x, target_y, identifier,
                                      alternate ? 8 : 1);
            if (result == 0) {
                return 0;
            }
            if (result == 1) {
                return 1;
            }
    }
    range = func_0812EED0(context, identifier);
    eligible = 0;
    dx = (s8)target_x - (s8)source_x;
    if (dx < 0) {
        dx = -dx;
    }
    dy = (s8)target_y - (s8)source_y;
    if (dy < 0) {
        dy = -dy;
    }
    if (dx + dy <= (s8)range) {
        eligible = 1;
    }
    return eligible;
}
