#include "ffta.h"

/* 0x0812F090..0x0812F0CA: 58 bytes. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

extern s32 func_0812E1A8(void *, u8, u8, u8, u8, u16, u8);

s32 func_0812F090(Unit *unit, u8 to_x, u8 to_y, u16 item, u8 flags)
{
    return func_0812E1A8(unit, unit->x, unit->y, to_x, to_y, item, flags);
}
