#include "ffta.h"

// 0x0811D73C..0x0811D8A4: 360 bytes.
typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    void **effect;
    u8 unknown_0C[16];
} Descriptor;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void **source;
    void *particle;
    void *particle_outputs[7];
    void *effect;
    InterpolationState transition;
    void *extra_effect;
} State;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

typedef struct {
    u8 unknown_00[0x30];
    u32 field_30;
} Struct080DBEB4;

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct PaletteTransition PaletteTransition;

extern const u8 data_083A6F2C[];
extern const SequenceEvent data_083A70B4[];

extern void func_080DBDC8(const PositionState *object, s16 *x, s16 *y);
extern int func_080DFAD0(int handle);
extern void func_080DC224(void *object, s16 width, s16 height, s16 *x, s16 *y);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_080DBEB4(Struct080DBEB4 *object, u8 value);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode,
                         u16 count, void **outputs, const void *resource,
                         void *context);
extern PaletteTransition *func_08147EC8(u16, u16, u16, u8);
extern void func_080E0608(InterpolationState *transition, s16 from,
                          s16 to, s16 duration);
extern void *func_080DFD8C(const SequenceEvent *resource, u8 parameter, u16 type,
                         u16 flags, void *context);
extern void func_080E064C(InterpolationState *transition);
extern void *func_081484CC(void *effect);
extern void *func_080D6134(void *handle);

u32 func_0811D73C(void *context, Descriptor *command, void *payload)
{
    State *state = payload;

    switch (command->phase) {
    case 0:
        state->object = command->value;
        state->source = command->effect;
        func_080DBDC8(state->object, &state->x, &state->y);
        break;
    case 0x100:
        state->timer = 25;
        command->phase++;
        break;
    case 0x101: {
        s16 screen_x;
        s16 screen_y;

        if (state->timer) {
            state->timer--;
            if (state->timer)
                break;
        }
        if (!(u8)func_080DFAD0((int)*state->source))
            break;
        func_080DC224(state->object, state->x, state->y, &screen_x, &screen_y);
        func_08003508(screen_x, 3);
        func_08003558(screen_y, 3);
        func_080DBEB4(state->object, 0);
        state->particle = func_080D6098(state->x, state->y, 0, 1, 7,
            state->particle_outputs, data_083A6F2C, context);
        state->effect = func_08147EC8(0x70, 0x10, 0x96, 8);
        func_080E0608(&state->transition, state->y, (s16)(state->y - 16),
            0x96);
        state->extra_effect = func_080DFD8C(data_083A70B4, 1, 4, 0, context);
        command->phase++;
        break;
    }
    case 0x102: {
        s16 screen_x;
        s16 screen_y;

        func_080E064C(&state->transition);
        func_080DC224(state->object, state->x, state->transition.current, &screen_x, &screen_y);
        func_08003508(screen_x, 3);
        func_08003558(screen_y, 3);
        state->effect = func_081484CC(state->effect);
        if (state->effect)
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        command->phase++;
        break;
    }
    case 1: /* Task destruction. */
        break;
    case 0x103:
        command->phase = 2;
        break;
    }
    return 0;
}
