#include "ffta.h"

typedef struct {
    s8 state;
    s8 value;
    s8 index;
    u8 counter;
    u8 flags;
    u8 special;
    u8 unknown_06[2];
    s16 offset;
    u16 timer;
} SequenceState;

extern u32 func_0809DA0C(void *object, u16 index);

/* 0x0809DCC4..0x0809DE00: 316 bytes. */
void func_0809DCC4(void *object, SequenceState *state)
{
    s32 remaining = state->flags & ~0x80;

    remaining--;

    if (remaining < 0)
        remaining = 0;
    state->flags = remaining | (state->flags & 0x80);
    if (remaining <= 0) {
        state->flags = (state->flags & 0x80) | 4;
        if (state->flags & 0x80) {
            state->offset++;
            if (state->offset > 1)
                state->flags ^= 0x80;
        } else {
            state->offset--;
            if (state->offset < -1)
                state->flags ^= 0x80;
        }
    }

    switch (state->state) {
    case 1:
        state->value = func_0809DA0C(object, (u16)state->index);
        state->index++;
        if (state->index > 24)
            state->index = 1;
        if (state->value != 0) {
            s32 value = (u16)state->value;

            state->special = value <= 13 ? value >= 10 : 0;
            state->state = 2;
            state->timer = 5;
            state->flags = (state->flags & 0x80) | 4;
        }
        break;
    case 2:
        if ((s16)--state->timer <= 0) {
            state->timer = 0;
            state->state = 3;
            if (state->counter >= 80)
                state->counter = 0;
        }
        break;
    case 3:
        state->counter++;
        if (state->counter >= 80) {
            u32 value;

            state->counter = 0;
            value = func_0809DA0C(object, (u16)(state->value + 1));
            if (state->value != value)
                state->state = 4;
        }
        break;
    case 4:
        state->timer++;
        if (state->timer > 5) {
            state->timer = 5;
            state->state = 0;
        }
        break;
    }
}
