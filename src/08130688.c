#include "ffta.h"

/* 0x08130688..0x081306E0: 88 bytes, 38 reachable instructions. */
typedef struct Unit Unit;
typedef struct {
    u8 unknown_00[0x1A];
    u8 modifiers[3];
    u8 unknown_1D[3];
} Equipment;

extern const Equipment g_table_0851D180[];
extern u32 func_080CCD50(u16, u8);
extern void func_080CDFE4(Unit *, u32);
extern void func_080CE420(Unit *, u32);

void func_08130688(u16 equipment_id, u16 action_id, Unit *unit)
{
    const Equipment *equipment;
    s32 i;

    if (equipment_id == 0)
        return;
    if (action_id && !func_080CCD50(action_id, 3))
        return;
    equipment = &g_table_0851D180[equipment_id];
    for (i = 0; i < 3; i++) {
        if (equipment->modifiers[i] == 0x3E) {
            func_080CDFE4(unit, 0);
            func_080CE420(unit, 0);
            break;
        }
    }
}
