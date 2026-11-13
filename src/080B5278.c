#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    u8 appearance;
    u8 unknown_20[0x60];
    void *owner;
} Context080B5278;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
} Queue080B5278;

typedef struct {
    Context080B5278 *context;
    u8 unknown_04[0x45];
    u8 appearance;
    u8 unknown_4A[0xA2];
    u16 action;
    u16 parameter;
    u16 unknown_F0;
    u16 count;
    u8 mode;
    u8 unknown_F5[2];
    u8 index;
    u8 slots[4];
    u16 actions[4];
    u8 field_104;
    u8 unknown_105;
    u8 field_106;
    u8 unknown_107;
    u8 step;
    u8 x;
    u8 z;
    u8 unknown_10B[0x1007];
    u16 flags;
    u8 unknown_1114[4];
    Queue080B5278 queue;
} State080B5278;

typedef struct {
    s32 x : 16;
    s32 y : 16;
    s32 z : 16;
    s32 unknown_06 : 16;
} Coordinates080B5278;

typedef struct {
    u8 unknown_00[0x26];
    u8 active;
    u8 unknown_27;
    Coordinates080B5278 current;
    Coordinates080B5278 target;
} Globals080B5278;

extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern Globals080B5278 g_state_0200F390;
extern s32 func_0812F0D8(void *, u16 *);
extern s32 func_080CCD50(u16, u32);
extern u8 func_080C8240(void *);
extern u8 func_0809A740(void *);
extern u8 func_0809A77C(void *);
extern u32 func_080C92F0(void *, u32);
extern s32 func_080B7C2C(u16, u16, u8);

static inline void push_state(Queue080B5278 *queue)
{
    queue->entries[queue->count++] = queue->current;
}

static inline u16 range_shape(void *unit, u16 first, u16 second, u8 mode)
{
    if (unit && (func_080C92F0(unit, 0x28) & 4)) {
        if (mode == 0)
            return 0x1C0;
        else
            return 0x1C2;
    }
    return func_080B7C2C(first, second, mode);
}

/* Complete [0x080B5278, 0x080B5518): 672 bytes. */
void func_080B5278(State080B5278 *state, Context080B5278 *context,
                   u16 action, u16 parameter, u8 first, u8 second, u8 mode)
{
    u32 flags = 0;
    u32 i;
    Coordinates080B5278 coordinates;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->mode = mode;
    state->context = context;
    state->action = action;
    if (first)
        flags |= 1;
    if (second)
        flags |= 2;
    state->flags = flags;
    state->count = func_0812F0D8(state->context->unit, &state->parameter);
    if (state->count == 0) {
        state->parameter = 0;
        state->count = 1;
    }
    if ((action && func_080CCD50(action, 0x1B)) || action == 0x109)
        state->parameter = parameter;

    state->queue.current = 0x1F;
    push_state(&state->queue);
    state->queue.current = 0x13;
    push_state(&state->queue);
    state->queue.current = 0x0D;
    for (i = 0; i < 4; i++) {
        state->slots[i] = 1;
        state->actions[i] = 4;
    }
    if (func_080C8240(context->unit))
        state->step = func_0809A740(context->owner);
    else
        state->step = func_0809A77C(context->owner);
    for (state->index = 0; state->index < 2; state->index++) {
        state->actions[state->index] = range_shape(state->context->unit,
            state->action, state->parameter, state->index);
        if ((state->actions[state->index] & 0xF) == 4 && state->index != 0)
            state->slots[state->index - 1] = state->index;
        else
            state->slots[state->index] = state->index;
    }
    state->index++;
    state->x = state->context->x >> 5;
    state->z = state->context->z >> 5;
    state->field_106 = 8;
    state->field_104 = 4;
    push_state(&state->queue);
    state->queue.current = 6;
    coordinates.x = state->context->x >> 5;
    coordinates.z = state->context->z >> 5;
    coordinates.y = state->context->y >> 4;
    g_state_0200F390.current = g_state_0200F390.target = coordinates;
    g_state_0200F390.active = 1;
    state->appearance = context->appearance;
}
