#include "ffta.h"

typedef struct PositionState {
    u8 unknown_00[0x64];
    u8 first;
    u8 second;
} PositionState;

typedef struct PositionOwner {
    u8 unknown_00[4];
    PositionState *position;
} PositionOwner;

extern PositionOwner *g_state_03002810;
extern u8 g_state_02000000[];

/* 08035FC4..0803600C: 72 bytes, 27 instructions. */
u8 func_08035FC4(void)
{
    PositionState *position = g_state_03002810->position;

    if (position->first != g_state_02000000[0x2FBB] ||
        position->second != g_state_02000000[0x2FBA])
        return 1;
    return 0;
}
