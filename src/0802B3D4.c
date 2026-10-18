/* 0x0802B3D4 - 92 bytes (the index calls it 48; it actually runs to 0x0802B430,
 * where `bx r1` returns) - MATCH.
 *
 * Advances the row pointer held in state->field_14 through the packed u16 array
 * state->data, returns state->first + state->first[index] and wraps field_14
 * round the end of the table.
 *
 * The two u16 loads at data + 4*field_14 and data + 4*field_14 + 2 are the two
 * halves of one 4-byte row, read separately.  Both addresses are re-derived
 * from state rather than held in a local: the strh to state->field_12 in
 * between is a u16 store and may alias state->field_14, so the second one has
 * to reload it, while the state->data load is a pointer load and survives.
 *
 * Target bytes:
 *   b5301c19688ada688000801800886804180c18598a31002582598880008018040888000400c884211d2
 *   5d828a98013098828919040004000c884208d37d98002800d0019d8203e01e4819820120183182
 *   01c30bc02bc0847
 */

#include "ffta.h"

typedef struct {
    void *first;
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
} State0802B3D4;

void *func_0802B3D4(State0802B3D4 *state)
{
    u8 *first = state->first;
    void *result;

    result = (u8 *)first
          + *(u32 *)((u8 *)first
                   + 4 * *(u16 *)((u8 *)state->data + state->field_14 * 4));
    state->field_12 = state->field_12 + 1;
    if (*(u16 *)((u8 *)state->data + state->field_14 * 4 + 2) < state->field_12) {
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
    return result;
}