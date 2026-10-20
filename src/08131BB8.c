#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

extern State g_state_02000080;

u8 func_08131BB8(void *record)
{
    s32 index;
    SceneRecord *candidate;

    for (index = 0, candidate = g_state_02000080.first; index < 24; candidate++, index++) {
        if (candidate == record)
            return 1;
    }
    return 0;
}
