/* 0x08017490 - 110 bytes + 8 bytes of literal pool.
 *
 * Same 0x2C-byte state record as 0x08017424: that function takes its first
 * three fields from arguments, this one copies them out of two IWRAM globals
 * one word in.  Both clear the same tail, in the same irregular order.
 *
 * field_00 <- *(u32 *)(0x030008B0 + 0x14)
 * field_04 <- *(u32 *)(0x03000990 + 0x14)
 */
#include "ffta.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017490;

/* Only the word at +0x14 is read out of either global; the bytes in front of
 * it are not identified. */
typedef struct {
    u8 unknown_00[0x14];
    u32 value_14;
} IwramSource;

void func_08017490(State08017490 *state,
                   u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                   u16 value_14, u16 value_18, u16 value_1A, u8 value_17)
{
    IwramSource *source00 = (IwramSource *)0x030008B0;
    IwramSource *source04 = (IwramSource *)0x03000990;
    u32 value00 = source00->value_14;
    u32 value04 = source04->value_14;
    u8 value16 = 0x20;

    state->field_00 = value00;
    state->field_04 = value04;
    state->field_10 = value_10;
    state->field_11 = value_11;
    state->field_12 = value_12;
    state->field_13 = value_13;
    state->field_14 = value_14;
    state->field_16 = value16;
    state->field_18 = value_18;
    state->field_1A = value_1A;
    state->field_17 = value_17;
    state->field_1F = 0;
    state->field_22 = 0;
    state->field_20 = 0;
    state->field_26 = 0;
    state->field_24 = 0;
    state->field_2A = 0;
    state->field_28 = 0;
    state->field_08 = 0;
    state->field_0C = 0;
    state->field_1E = 0;
    state->field_1D = 0;
    state->field_1C = 0;
}