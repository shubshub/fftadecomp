#include "ffta.h"

/* 0x080CB7C0..0x080CB808: 72 bytes, including the literal pool. */
typedef struct {
    u8 unknown_00[4];
    u8 index;
} Unit;

extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(Unit *unit);
extern u8 func_080C92F0(Unit *unit, u32 field);

u8 func_080CB7C0(Unit *unit, u8 selector)
{
    if (func_080C817C(unit)) {
        const u8 *entry = g_table_085273D8[unit->index];
        if (selector == 1)
            return entry[12];
        return entry[13];
    } else {
        u32 field = 11;
        if (selector == 1)
            field = 10;
        return func_080C92F0(unit, field);
    }
}
