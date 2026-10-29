#include "ffta.h"

typedef struct {
    u16 unknown_00 : 5;
    s16 value : 8;
    u16 unknown_0D : 3;
} PackedCoordinate080B5518;

typedef struct {
    void *unit;
    u32 unknown_04;
    PackedCoordinate080B5518 x;
    PackedCoordinate080B5518 y;
} UnitPosition080B5518;

extern u16 func_0812EACC(void *first, void *second, u16 ability,
                       s32 first_x, s32 first_y, s32 second_x, s32 second_y);

/* Complete target: [0x080B5518, 0x080B55CC), 180 bytes, 84 instructions. */
u8 func_080B5518(UnitPosition080B5518 *first,
                UnitPosition080B5518 *second, u16 ability)
{
    if (ability == 0xE9) {
        u32 result = 0;
        s32 index;

        for (index = 0; index < 8; index++) {
            if (func_0812EACC(first->unit, second->unit, index + 0x44,
                              first->x.value, first->y.value,
                              second->x.value, second->y.value))
                result |= 1;
        }
        return result;
    }

    if (ability == 0x149)
        ability = 0x139;
    return func_0812EACC(first->unit, second->unit, ability,
                          first->x.value, first->y.value,
                          second->x.value, second->y.value) != 0;
}
