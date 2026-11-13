#include "ffta.h"

// func_080B5278: complete target [0x080B5278, 0x080B5518), 672 bytes,
// 308 instructions.

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[0x11];
    u8 unknown_1F;
    u8 unknown_20[0x60];
    void *unknown_80;
} Context080B5278;

typedef struct {
    s16 x;
    s16 height;
    s16 y;
    s16 unknown_06;
} Position080B5278;

typedef struct {
    u16 current;
    u16 depth;
    u16 stack[34];
} Phases080B5278;

typedef struct {
    Context080B5278 *context;
    u8 unknown_004[0x45];
    u8 unknown_049;
    u8 unknown_04A[0xA2];
    u16 action;
    u16 parameter;
    u8 unknown_0F0[2];
    u16 count;
    u8 argument6;
    u8 unknown_0F5[2];
    u8 index;
    u8 slots[4];
    u16 shapes[4];
    u8 unknown_104;
    u8 unknown_105;
    u8 unknown_106;
    u8 unknown_107;
    u8 selected;
    u8 x;
    u8 y;
    u8 unknown_10B[0x1007];
    u16 flags;
    u8 unknown_1114[4];
    Phases080B5278 phases;
} State080B5278;

typedef struct {
    u8 unknown_00[0x26];
    u8 unknown_26;
    u8 unknown_27;
    Position080B5278 target;
    Position080B5278 cursor;
} Globals080B5278;

extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern Globals080B5278 g_state_0200F390;
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080C8240(const void *object);
extern u8 func_0809A740(void *context);
extern u8 func_0809A77C(void *context);
extern u32 func_080C92F0(void *unit, u32 selector);
extern u16 func_080B7C2C(u16 first, u16 second, u8 mode);

static inline u16 range_shape(void *unit, u16 first, u16 second, u8 mode)
{
    if (unit && (func_080C92F0(unit, 0x28) & 4)) {
        if (mode == 0)
            return 0x1c0;
        else
            return 0x1c2;
    }
    return func_080B7C2C(first, second, mode);
}

static inline void push_phase(Phases080B5278 *phases)
{
    phases->stack[phases->depth++] = phases->current;
}

void func_080B5278(State080B5278 *state, Context080B5278 *context,
                   u16 action, u16 parameter, u8 argument4, u8 argument5,
                   u8 argument6)
{
    Position080B5278 position;
    u32 i;
    u16 flags;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->argument6 = argument6;
    state->context = context;
    state->action = action;
    flags = argument4 != 0;
    if (argument5)
        flags |= 2;
    state->flags = flags;
    state->count = func_0812F0D8(state->context->unit, &state->parameter);
    if (state->count == 0) {
        state->parameter = 0;
        state->count = 1;
    }
    if ((action && func_080CCD50(action, 0x1B)) || action == 0x109)
        state->parameter = parameter;

    state->phases.current = 0x1F;
    push_phase(&state->phases);
    state->phases.current = 0x13;
    push_phase(&state->phases);
    state->phases.current = 0xD;

    for (i = 0; i < 4; i++) {
        state->slots[i] = 1;
        state->shapes[i] = 4;
    }

    if (func_080C8240(context->unit))
        state->selected = func_0809A740(context->unknown_80);
    else
        state->selected = func_0809A77C(context->unknown_80);

    for (state->index = 0; state->index < 2; state->index++) {
        state->shapes[state->index] = range_shape(state->context->unit,
            state->action, state->parameter, state->index);
        if ((state->shapes[state->index] & 0xF) == 4 && state->index != 0)
            state->slots[state->index - 1] = state->index;
        else
            state->slots[state->index] = state->index;
    }
    state->index++;

    state->x = state->context->x >> 5;
    state->y = state->context->y >> 5;
    state->unknown_106 = 8;
    state->unknown_104 = 4;
    push_phase(&state->phases);
    state->phases.current = 6;

    position.x = state->context->x >> 5;
    position.y = state->context->y >> 5;
    position.height = state->context->height >> 4;
    g_state_0200F390.cursor = position;
    g_state_0200F390.target = position;
    g_state_0200F390.unknown_26 = 1;
    state->unknown_049 = context->unknown_1F;
}
