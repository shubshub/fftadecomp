#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAA];
    u8 selection;
} SelectionState;

typedef struct {
    u8 unknown_00[4];
    SelectionState *selection;
} MenuContext;

typedef struct {
    u8 type : 5;
    u8 unknown_05 : 1;
    u8 enabled : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[5];
} __attribute__((packed)) SelectionRecord;

typedef struct {
    u8 unknown_0000[0x2E36];
    SelectionRecord records[5];
    u8 type : 5;
    u8 unknown_2E54_high : 3;
} GameState;

extern MenuContext *g_state_03002810;
extern GameState g_state_02000000;

/* Complete target: [0x08030168, 0x080301B0), 72 bytes, 28 instructions. */
void func_08030168(void)
{
    s32 index = g_state_03002810->selection->selection;
    GameState *state = &g_state_02000000;

    index--;
    if (state->records[index].type == state->type)
        state->records[index].enabled = 1;
}
