#include "ffta.h"

/* 0x080A8DB8: 82 bytes. */
typedef struct {
    u16 graphic;
    u16 duration;
} AnimationEntry;

typedef struct {
    const u8 *graphics;
    u8 unknown_04[0x0a];
    s16 index;
    s16 remaining;
    u16 unknown_12;
    const u8 *current;
    const u8 *script;
    u8 unknown_1c;
    u8 playing;
} AnimationState;

void func_080A8DB8(AnimationState *state)
{
    const u8 *script;
    const AnimationEntry *entry;

    state->remaining--;
    if (state->remaining <= 0) {
        state->current = 0;
        state->remaining = 0;
        script = state->script;
        if (((script[1] << 8) | script[0]) <= state->index)
            state->playing = 0;
        else {
            entry = (const AnimationEntry *)(script + 2) + state->index;
            state->current = state->graphics +
                ((const u32 *)state->graphics)[entry->graphic];
            state->index++;
            state->remaining = entry->duration;
        }
    }
}
