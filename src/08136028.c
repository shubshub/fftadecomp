#include "ffta.h"

/* 0x08136028 - 92 bytes, indexed as 48.
 *
 * The index stops at 0x08136058 because the `bhs` at the end of that block
 * targets 0x0813607C, which the splitter treated as a separate entry; the
 * bytes from 0x08136058 to 0x08136084 are this function's own tail and the
 * next indexed function does not start until 0x08136084.
 *
 * `first` is a table of 32-bit byte offsets.  `data` is an array of
 * (offset, count) pairs of u16; entry 0 of the current pair is an index into
 * `first`, entry 1 is how many items that entry has.  field_12 is the position
 * inside the current entry, field_14 the current entry, field_16 the
 * wrap-to-first flag, field_18 the wrap-to-last flag.
 */
typedef struct {
    u32 *first;
    u8 *source;
    u16 count;
    u8 unknown_0A[2];
    u16 *data;
    u16 index;
    u16 field_12;
    u16 field_14;
    u8 field_16;
    u8 unknown_17;
    u16 field_18;
} State08136028;

void *func_08136028(State08136028 *state)
{
    u8 *table;
    u8 *current;

    table = (u8 *)state->first;
    current = table + *(u32 *)(table + 4 * ((u16 *)((u8 *)state->data
                                                    + state->field_14 * 4))[0]);
    state->field_12 = state->field_12 + 1;

    if (((u16 *)((u8 *)state->data + state->field_14 * 4))[1] < state->field_12) {
        state->field_12 = 0;
        state->field_14 = state->field_14 + 1;

        if (state->field_14 >= state->count) {
            if (state->field_16) {
                state->field_14 = 0;
            } else {
                state->field_14 = state->count - 1;
                state->field_18 = 1;
            }
        }
    }

    return current;
}