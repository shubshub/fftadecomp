#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

extern SceneRecord g_state_02002FC4[12];
extern State g_state_02000080;

SceneRecord *func_080C83CC(u8 category)
{
    SceneRecord *record;
    s32 count;
    s32 index;

    if (category < 2)
        return 0;
    record = g_state_02002FC4;
    count = 12;
    for (index = 0; index < count; index++, record++) {
        if (record->unknown_00[4] == category)
            return record;
    }
    record = g_state_02000080.first;
    count = 24;
    for (index = 0; index < count; index++, record++) {
        if (record->unknown_00[4] == category)
            return record;
    }
    return 0;
}
