#include "ffta.h"

typedef struct {
    s8 state;
    s8 value;
    s8 index;
    u8 counter;
    u8 flags;
    u8 value_in_10_to_13;
    u8 unknown_06[2];
    s16 offset;
    u16 timer;
} State0809DCC4;

extern u32 func_0809DA0C(void *object, u16 selector);

/* The ROM narrows the s8 value to u16 (lsls/lsrs #16) before a signed
 * cmp #13 / cmp #10 range test and joins 1 and 0 in r0 ahead of the byte
 * store.  The caller func_0809F938 is the same switch over 2..4 as a
 * function of its own. */
static inline u8 is_value_10_to_13(u16 value)
{
    switch (value) {
    case 10:
    case 11:
    case 12:
    case 13:
        return 1;
    default:
        return 0;
    }
}

/* Target: [0x0809DCC4, 0x0809DE00), 316 bytes, 156 instructions, no literals. */
void func_0809DCC4(void *object, State0809DCC4 *state)
{
    s32 remaining = state->flags & ~0x80;
    s32 value;

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
        state->value = func_0809DA0C(object, state->index);
        state->index++;
        if (state->index > 24)
            state->index = 1;
        if (state->value != 0) {
            state->value_in_10_to_13 = is_value_10_to_13(state->value);
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
            state->counter = 0;
            value = state->value;
            value = func_0809DA0C(object, value + 1);
            if (value != state->value)
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
