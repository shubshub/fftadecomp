#include "ffta.h"

/* 0x080CB450..0x080CB48C: 60 bytes, including the literal pool. */
typedef struct Unit Unit;

extern const u32 data_0851D0F4[];
extern u32 func_080C92F0(Unit *unit, u32 field);
extern u32 func_080CA7A4(u16 id, u32 field);

u32 func_080CB450(Unit *unit, u16 id)
{
    u32 mask = data_0851D0F4[func_080C92F0(unit, 36)];
    u8 category = func_080CA7A4(id, 3);
    u32 result = mask & (1u << (category - 1));

    if (result != 0)
        result = 1;
    return result;
}
