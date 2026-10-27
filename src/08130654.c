#include "ffta.h"

/* 0x08130654..0x08130688: 52 bytes, 24 instructions. */
typedef struct {
    u8 unknown_00[0x1A];
    u8 modifiers[3];
    u8 unknown_1D[3];
} Equipment;

extern const Equipment g_table_0851D180[];

u8 func_08130654(u16 equipment_id)
{
    const Equipment *equipment;
    s32 index;

    if (equipment_id == 0)
        return 0;
    equipment = &g_table_0851D180[equipment_id];
    for (index = 0; index < 3; index++) {
        if (equipment->modifiers[index] == 0x3D)
            return 1;
    }
    return 0;
}
