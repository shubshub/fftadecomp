#include "ffta.h"

/* 0x0812FA90..0x0812FAFC: 108 bytes, 50 reachable instructions. */
typedef struct Unit Unit;
typedef struct {
    u8 unknown_00[0x1A];
    u8 modifiers[3];
    u8 unknown_1D[3];
} Equipment;

extern const Equipment g_table_0851D180[];
extern u32 func_080C7EA4(const Unit *, u8);
extern u16 func_0812F914(u8, u16, u8);

u16 func_0812FA90(const Unit *unit, u8 category, u8 value)
{
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        u32 identifier = func_080C7EA4(unit, i + 29);

        if (identifier) {
            const Equipment *equipment = &g_table_0851D180[identifier];

            for (j = 0; j < 3; j++)
                value = func_0812F914(category, (s8)value,
                                       equipment->modifiers[j]);
        }
    }
    return (s8)value;
}
