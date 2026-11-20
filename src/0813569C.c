#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x3C33];
    u8 count;
    u16 entries[256];
} SelectionState;

typedef struct {
    u8 unknown_00[16];
} SelectionEntry;

struct Actor080C2618;

extern SelectionState g_state_02000000;
extern const SelectionEntry g_table_08528F34[];
extern s32 func_0812F0D8(const void *unit, u16 *items);
extern s32 func_08130200(void *source, void *target, u16 action, u16 equipment,
                         u16 attribute, u16 mode);
extern u8 func_081343C8(void *source, void *target, u16 value, u8 mode,
                        u32 flags, s16 amount, const void *data,
                        const SelectionEntry *entry);

/* Complete [0x0813569C, 0x08135750): 180 bytes, including literal pools. */
u8 func_0813569C(struct Actor080C2618 *source, struct Actor080C2618 *target,
                 u16 action, u32 mode)
{
    u8 selection_mode = mode;
    u16 items[2];
    s32 index;

    if (!func_0812F0D8(source, items))
        items[0] = 0;

    for (index = 0; index < g_state_02000000.count; index++) {
        if (func_081343C8(source, target, action, selection_mode, 0,
                          func_08130200(source, target, action, items[0], 0, 2),
                          0, &g_table_08528F34[g_state_02000000.entries[index]]))
            return index + 1;
    }
    return 0;
}
