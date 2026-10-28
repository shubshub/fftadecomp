#include "ffta.h"

/* 0x080901A8..0x08090214: 108 bytes. */
typedef struct {
    u8 *values;
    s16 center;
    s16 radius;
    s16 extent;
} GradientState;

void func_080901A8(GradientState *state)
{
    s32 offset;

    for (offset = state->radius; offset >= 0; --offset) {
        u32 distance = state->extent - offset;
        u8 *values;
        u16 first;
        u16 second;
        s16 position;
        u8 first_byte;
        u8 second_byte;

        if (offset >= state->extent) {
            first = 0;
            second = 16;
        } else if (distance <= 8) {
            first = 16;
            second = 16 - distance;
        } else {
            first = 16;
            second = 9;
        }

        position = state->center + offset;
        first_byte = first;
        second_byte = second;
        values = state->values;
        *(values + position * 2) = first_byte;
        ++values;
        *(values + position * 2) = second_byte;

        position = state->center - offset;
        values = state->values;
        *(values + position * 2) = first_byte;
        ++values;
        *(values + position * 2) = second_byte;
    }
}
