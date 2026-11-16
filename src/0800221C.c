#include "ffta.h"

/* Complete [0x0800221C, 0x080023D0): 436 bytes, 213 instructions, two
 * literal words and one padding halfword.
 * Updates a key-input state from the current key mask: edge bits,
 * held-key repeat with first/next delays, and the lowest repeating key. */

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeat;
    u8 repeat_key;
    u8 flags;
    u16 repeat_mask;
    u8 first_delay;
    u8 next_delay;
    u16 last_keys;
    u8 timer;
    u8 hold_limit;
    u8 hold_count;
} KeyState0800221C;

typedef struct {
    u8 code_0;
    u8 code_1;
    u8 unknown_02[3];
    u8 enabled;
} Control0800221C;

typedef struct {
    u8 unknown_00[3];
    u8 current;
} Runner0800221C;

extern Control0800221C data_03000ED0;
extern Runner0800221C data_03000E10;

/* The 1-based index of the lowest key in keys & mask, or 0 when there is
 * none; the ROM has it twice (0x0800230E-0x0800232C, 0x08002380-0x0800239E). */
static inline u8 first_key(u16 keys, u16 mask)
{
    u16 bit;
    u16 i;

    keys &= mask;
    bit = 1;
    for (i = 0; i < 10; i++) {
        if (bit & keys)
            return i + 1;
        bit <<= 1;
    }
    return 0;
}

void func_0800221C(KeyState0800221C *state, u16 keys)
{
    if (!data_03000ED0.enabled)
        return;

    if (keys == 0xF) {
        /* A, B, Select and Start: the ROM stores 0xA3, 0x5D and spins
         * (0x08002232-0x08002238; b . at 0x0800223A). */
        data_03000ED0.code_0 = 0xA3;
        data_03000ED0.code_1 = 0x5D;
        for (;;)
            ;
    }

    if (!(state->flags & 0x10) && data_03000E10.current != 0xFF)
        return;

    if (state->flags & 1) {
        if (state->flags & 8) {
            state->pressed = keys & ~state->held;
            state->repeat = state->pressed & ~state->repeat_mask;
            state->held = keys;
            state->flags ^= 8;
        } else {
            state->pressed = (keys & ~state->held) | state->pressed;
            state->repeat = (state->pressed & ~state->repeat_mask) | state->repeat;
            state->held |= keys;
        }
    } else {
        state->pressed = keys & ~state->held;
        state->repeat = state->pressed & ~state->repeat_mask;
        state->held = keys;
    }

    keys &= 0xF0;
    if ((state->flags & 2) && state->last_keys == keys) {
        if (keys != 0 && state->hold_count >= state->hold_limit) {
            state->flags |= 0x20;
        } else {
            state->flags &= ~0x20;
            state->hold_count++;
        }

        if (!(state->flags & 0xC0)) {
            state->timer = state->first_delay;
            state->flags |= 0x40;
            state->repeat |= keys & state->repeat_mask;
            state->repeat_key = first_key(keys, state->repeat_mask);
            if (state->flags & 4)
                state->pressed = keys & ~state->held;
        } else {
            state->repeat_key = 0;
            if (state->flags & 0x40) {
                if (state->timer == 0) {
                    /* The ROM stores the zero timer back
                     * (strb r1, [r4, #0xe] at 0x0800234C). */
                    state->timer = 0;
                    state->flags = (state->flags ^ 0x40) | 0x80;
                } else {
                    state->timer--;
                }
            } else if (state->flags & 0x80) {
                if (state->timer != 0) {
                    state->timer--;
                } else {
                    state->timer = state->next_delay;
                    state->repeat |= keys & state->repeat_mask;
                    state->repeat_key = first_key(keys, state->repeat_mask);
                    if (state->flags & 4)
                        state->pressed = keys & ~state->held;
                }
            }
        }
    } else if (!(keys & state->last_keys)) {
        state->flags &= 0xF;
        state->timer = 0;
        state->hold_count = 0;
        state->repeat_key = 0;
    }
    state->last_keys = keys;
}
