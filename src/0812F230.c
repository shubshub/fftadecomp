#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 first;
    u16 second;
    u8 unknown_10[0x10];
    u16 position[2];
    u16 unknown_24;
    u16 flags;
    u8 cursor;
    u8 unknown_29[3];
    const u8 *entry;
    const u32 *metadata;
} State0812F230;

extern void (*g_callbacks_0836D4B8[])(void *object, u32 size);
extern const u8 *func_080CCD50(u16 identifier, u32 type);
extern const u32 data_08553E70[];

/* 0x0812F230: 116 bytes; reset the state while retaining its position. */
void func_0812F230(State0812F230 *state, u16 first, u16 second, u8 mode)
{
    u16 position[2];

    position[0] = state->position[0];
    position[1] = state->position[1];
    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->position[0] = position[0];
    state->position[1] = position[1];
    state->flags = mode ? 0 : 0x80;
    state->entry = func_080CCD50(first, 9);
    state->first = first;
    state->second = second;
    state->cursor = 0;
    state->metadata = data_08553E70 + state->entry[0];
}
