#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Completion081276D8;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u16 height;
    s16 y;
} Object081276D8;

typedef struct {
    u16 value;
    u8 unknown_02[22];
} Ramp081276D8;

typedef struct {
    Completion081276D8 *completion;
    Object081276D8 *object;
    s16 x;
    s16 y;
    u16 value;
    u8 flags;
    u8 animation;
    u8 unknown_10[8];
    Ramp081276D8 first;
    Ramp081276D8 second;
} State081276D8;

extern void func_080076F4(Ramp081276D8 *ramp);
extern u32 func_08127C94(State081276D8 *state);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern u32 func_0809A53C(Object081276D8 *object);
extern u32 func_08127380(State081276D8 *state);
extern void func_0809A530(void *object, u32 value);
extern u32 func_08007894(const void *ramp);

/* Complete target: [0x081276D8, 0x081277C8), 240 bytes. */
u16 func_081276D8(State081276D8 *state)
{
    u16 status = 0x102;
    u32 first_complete;
    u32 second_complete;

    func_080076F4(&state->first);
    state->object->x = state->first.value;
    func_080076F4(&state->second);
    state->object->y = state->second.value;

    if ((u8)func_08127C94(state)) {
        u32 animation;
        u8 changed;

        state->object->height = func_0801CC18((u8)(state->object->x >> 5),
                                              (u8)(state->object->y >> 5)) << 4;
        func_0809A570(state->object, 0, 0x100);
        state->animation = func_0809A53C(state->object);
        if (state->animation != 0)
            state->animation--;

        animation = func_08127380(state);
        if (animation != state->animation) {
            state->animation = animation;
            changed = 1;
        } else {
            changed = 0;
        }
        if (changed)
            func_0809A530(state->object, state->animation);
        status = 0x101;
    }

    first_complete = func_08007894(&state->first);
    second_complete = func_08007894(&state->second);
    if (first_complete && second_complete) {
        state->object->height = func_0801CC18((u8)(state->object->x >> 5),
                                              (u8)(state->object->y >> 5)) << 4;
        func_0809A570(state->object, 0, 0x100);
        state->completion->complete = 1;
        status = 3;
    }
    return status;
}
