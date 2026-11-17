#include "ffta.h"

// 0x0811D73C..0x0811D8A4: 360 bytes.
typedef struct {
    s16 value;
    u8 unknown_02[10];
} HeightTransition;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    void *source;
} Command;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    u32 *source;
    u32 particle;
    u8 particle_data[28];
    u32 effect;
    HeightTransition transition;
    u32 extra_effect;
} State;

extern const u8 data_083A6F2C[];
extern const u8 data_083A70B4[];

extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern u8 func_080DFAD0(u32 value);
extern void func_080DC224(void *object, s16 width, s16 height, s16 *x, s16 *y);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_080DBEB4(void *object, u8 value);
extern u32 func_080D6098(s16 x, s16 y, u32 flags, u32 enabled,
                         u32 count, void *data, const void *resource,
                         void *context);
extern u32 func_08147EC8(u16, u16, u16, u8);
extern void func_080E0608(HeightTransition *transition, s16 from,
                          s16 to, u16 duration);
extern u32 func_080DFD8C(const void *resource, u8 parameter, u32 type,
                         u32 flags, void *context);
extern void func_080E064C(HeightTransition *transition);
extern u32 func_081484CC(u32 effect);
extern u32 func_080D6134(u32 handle);

u32 func_0811D73C(void *context, Command *command, State *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        state->source = command->source;
        func_080DBDC8(state->object, &state->x, &state->y);
        break;
    case 0x100:
        state->timer = 25;
        command->state++;
        break;
    case 0x101: {
        s16 a;
        s16 b;

        if (state->timer) {
            state->timer--;
            if (state->timer)
                break;
        }
        if (!func_080DFAD0(*state->source))
            break;
        func_080DC224(state->object, state->x, state->y, &a, &b);
        func_08003508(a, 3);
        func_08003558(b, 3);
        func_080DBEB4(state->object, 0);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 7,
            state->particle_data, data_083A6F2C, context);
        state->effect = func_08147EC8(0x70, 0x10, 0x96, 8);
        func_080E0608(&state->transition, state->y, (s16)(state->y - 16),
            0x96);
        state->extra_effect = func_080DFD8C(data_083A70B4, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x102: {
        s16 a;
        s16 b;

        func_080E064C(&state->transition);
        func_080DC224(state->object, state->x, state->transition.value, &a, &b);
        func_08003508(a, 3);
        func_08003558(b, 3);
        state->effect = func_081484CC(state->effect);
        if (state->effect)
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        command->state++;
        break;
    }
    case 1:
        break;
    case 0x103:
        command->state = 2;
        break;
    }
    return 0;
}
