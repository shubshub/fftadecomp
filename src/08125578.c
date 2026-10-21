#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0x108 - 0x2A];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
} State;

extern State g_state_02000080;

void *func_080C83CC(u8 category);
void *func_08121CB4(u8 index);

void *func_08125578(u8 selector)
{
    SceneRecord *record;
    s32 index;

    if (selector != 0xFF) {
        if ((s8)selector < 0)
            return func_08121CB4(selector);
        return func_080C83CC(selector);
    }

    record = g_state_02000080.first;
    for (index = 0; index < 24; index++, record++) {
        if (record->flags & 0x400)
            return record;
    }
    return 0;
}
