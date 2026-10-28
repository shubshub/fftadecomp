#include "ffta.h"

typedef struct {
    u8 unknown_00[0xFD];
    u8 terrain_movement;
} Unit;

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);

/* Complete [0x0812F0E4, 0x0812F122): 62 bytes, 29 instructions. */
u8 func_0812F0E4(const Unit *unit, u8 column, u8 row)
{
    if (func_0801CC7C(column, row) &&
        (unit->terrain_movement != 2 || !(func_0801CD08(column, row) & 2)))
        return 1;
    return 0;
}
