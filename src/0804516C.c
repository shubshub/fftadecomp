#include "ffta.h"

/* 0x0804516C..0x08045260: 244 bytes. */
typedef struct {
    u16 unknown_00;
    u8 active;
    u8 id;
} ChoiceSlot;

typedef struct {
    ChoiceSlot slots[4];
    u8 unknown_10[4];
} ChoiceRecord;

typedef struct {
    u8 unknown_00[0x67C];
    ChoiceRecord *records;
} ChoiceState;

typedef struct {
    u8 unknown_00[0x2E58];
    u8 flags;
} GameState;

extern GameState g_state_02000000;
extern ChoiceState *g_state_03002810;

u8 func_0804516C(u8 index, u8 *output)
{
    u32 id;
    u8 count = 0;
    u8 excludedA = 0xFF;
    u8 excludedB = 0xFF;
    GameState *state = &g_state_02000000;

    if (!(state->flags & 1))
        excludedA = 8;
    if (!(state->flags & 2))
        excludedB = 0x1B;
    if (g_state_03002810->records[index].slots[0].active) {
        id = g_state_03002810->records[index].slots[0].id;

        if (id != excludedA && id != excludedB) {
            output[count] = id;
            ++count;
        }
    }
    if (g_state_03002810->records[index].slots[1].active) {
        id = g_state_03002810->records[index].slots[1].id;

        if (id != excludedA && id != excludedB) {
            output[count] = id;
            ++count;
        }
    }
    if (g_state_03002810->records[index].slots[2].active) {
        id = g_state_03002810->records[index].slots[2].id;

        if (id != excludedA && id != excludedB) {
            output[count] = id;
            ++count;
        }
    }
    if (g_state_03002810->records[index].slots[3].active) {
        id = g_state_03002810->records[index].slots[3].id;

        if (id != excludedA && id != excludedB) {
            output[count] = id;
            ++count;
        }
    }
    return count;
}
