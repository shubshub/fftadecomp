#include "ffta.h"

/* 0x080F3F7C..0x080F40DA: complete 350-byte callback. */
typedef struct {
    u16 x;
    u16 y;
} Position;

typedef struct {
    u16 phase;
    u16 unknown_02;
    const Position *position;
    u8 unknown_08[12];
    u8 delay;
    u8 unknown_15;
    u16 variant;
} TaskDescriptor;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u8 variant;
    u8 delay;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *objects[2];
    InterpolationState motion;
} CallbackState;

extern const u8 data_084F6130[];
extern void *func_080D5CC0(const void *, u32, s16, s16, u16, u8, u32, u32);
extern void func_08011058(void *, s16);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void *func_08011484(void *);
extern void func_080107D4(void *, s16, s16, s16);
extern u8 func_080E0690(InterpolationState *);
extern void func_080D5F74(void **, u16);

u32 func_080F3F7C(void *task, TaskDescriptor *descriptor, CallbackState *state)
{
    switch (descriptor->phase) {
    case 0: {
        const Position *position = descriptor->position;
        u16 vertical_offset = -52;
        state->delay = descriptor->delay + 1;
        state->variant = descriptor->variant;
        state->x = position->x;
        state->y = vertical_offset + position->y;
        break;
    }
    case 0x100:
        if (--state->delay)
            break;
        state->objects[0] = func_080D5CC0(data_084F6130, 6,
            state->x, state->y, 0x34D, 6, 1, 0);
        state->objects[1] = func_080D5CC0(data_084F6130, 7,
            state->x, state->y, 0x34D, 6, 1, 0);
        func_08011058(state->objects[0], 4 - state->variant);
        func_08011058(state->objects[1], 4 - state->variant);
        func_080E0608(&state->motion, state->y, state->y + 40, 34);
        descriptor->phase++;
        break;
    case 0x101: {
        u8 i;
        func_080E064C(&state->motion);
        for (i = 0; i < 2; i++) {
            state->objects[i] = func_08011484(state->objects[i]);
            if (state->objects[i])
                func_080107D4(state->objects[i], state->x,
                              state->motion.current, 0);
        }
        if (func_080E0690(&state->motion))
            descriptor->phase++;
        break;
    }
    case 0x102:
        func_080D5F74(state->objects, 2);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
