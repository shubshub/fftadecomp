#include "ffta.h"

typedef struct {
    u16 remaining;
    u8 interval;
} Transition;

typedef struct {
    u16 active;
    u16 flags;
    u16 unknown_04;
    u16 first;
    u16 last;
    u16 unknown_0A;
    Transition transition;
} UpdateState;

typedef struct {
    u16 color;
    s16 red_accumulator;
    s16 green_accumulator;
    s16 blue_accumulator;
    s8 red_delta;
    s8 green_delta;
    s8 blue_delta;
} PaletteEntry;

typedef struct {
    s16 red;
    s16 green;
    s16 blue;
} Components;

extern u16 data_03003860[];
extern PaletteEntry data_03003E68[];

/* Target: complete [0x081465E8, 0x08146864), 636 bytes. */
void func_081465E8(UpdateState *state)
{
    Transition *transition = &state->transition;
    u8 interval = transition->interval;
    u16 index;

    if (transition->remaining == 1) {
        for (index = state->first; index <= state->last; index++)
            data_03003860[index] = data_03003E68[index].color;
        state->active = 0;
        return;
    }

    for (index = state->first; index <= state->last; index++) {
        Components components;
        u8 amount;
        s8 direction;
        u32 change;

        if ((state->flags & 0x10) && !(index & 0xF))
            continue;

        components.red = data_03003860[index] & 0x1F;
        components.green = (data_03003860[index] & 0x3E0) >> 5;
        components.blue = (data_03003860[index] & 0x7C00) >> 10;

        direction = 1;
        change = 1;
        amount = data_03003E68[index].red_delta;
        if (data_03003E68[index].red_delta < 0) {
            amount = -data_03003E68[index].red_delta;
            direction = -1;
            change = components.red != 0;
        } else if (components.red == 31) {
            change = 0;
        }
        if (change) {
            data_03003E68[index].red_accumulator -= (s8)amount;
            while (data_03003E68[index].red_accumulator < 0) {
                components.red += direction;
                data_03003E68[index].red_accumulator += interval;
            }
        }

        direction = 1;
        change = 1;
        amount = data_03003E68[index].green_delta;
        if (data_03003E68[index].green_delta < 0) {
            amount = -data_03003E68[index].green_delta;
            direction = -1;
            change = components.green != 0;
        } else if (components.green == 31) {
            change = 0;
        }
        if (change) {
            data_03003E68[index].green_accumulator -= (s8)amount;
            while (data_03003E68[index].green_accumulator < 0) {
                components.green += direction;
                data_03003E68[index].green_accumulator += interval;
            }
        }

        direction = 1;
        change = 1;
        amount = data_03003E68[index].blue_delta;
        if (data_03003E68[index].blue_delta < 0) {
            amount = -data_03003E68[index].blue_delta;
            direction = -1;
            change = components.blue != 0;
        } else if (components.blue == 31) {
            change = 0;
        }
        if (change) {
            data_03003E68[index].blue_accumulator -= (s8)amount;
            while (data_03003E68[index].blue_accumulator < 0) {
                components.blue += direction;
                data_03003E68[index].blue_accumulator += interval;
            }
        }

        data_03003860[index] = (components.green << 5) | components.red |
                              (components.blue << 10);
    }
    transition->remaining--;
}
