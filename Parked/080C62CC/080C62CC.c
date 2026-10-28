#include "ffta.h"

typedef struct {
    u32 items[24];
    u8 mode;
    u8 unknown_61;
    u8 count;
    u8 unknown_63[3];
    u16 saved_control;
    u16 saved_attributes;
    u16 unknown_6A;
    u16 current;
    u16 depth;
    u16 history[34];
} State080C62CC;

typedef struct {
    u8 frame;
    u8 flags;
    u8 index;
    u8 requested_index;
    s16 x;
    s16 y;
    u8 unknown_08[0x40];
    u16 state;
    u8 unknown_4A[0x46];
} Animation080C62CC;

typedef struct {
    u16 control;
    u8 unknown_02[0x48];
    u8 attributes : 8;
} Display080C62CC;

typedef void (*BufferInitializer080C62CC)(void *destination, u32 bytes);
typedef void (*BufferCopier080C62CC)(void *destination, const void *source,
                                    u32 bytes);

extern BufferInitializer080C62CC g_callbacks_0836D4B8[];
extern BufferCopier080C62CC data_0836D4BC;
extern u8 data_03003A60[];
extern Animation080C62CC data_02015744;
extern Display080C62CC g_control_flags_03000940;
extern const u8 *func_080CBA3C(u8 index);
extern u8 func_080C95A8(u16 index);

static inline void push_state(State080C62CC *state)
{
    state->history[state->depth++] = state->current;
}

static inline void request_animation(u16 request)
{
    u8 value;
    Animation080C62CC *animation;

    if (!func_080C95A8(13))
        return;
    value = request;
    animation = &data_02015744;
    if (animation->index) {
        if (animation->index == value)
            return;
        animation->flags |= 4;
        animation->requested_index = value;
    } else {
        g_callbacks_0836D4B8[0](animation, sizeof(*animation));
        animation->index = value;
        animation->x = 0xD8;
        animation->y = 0x98;
        if (value)
            animation->state = 1;
    }
}

/* 0x080C62CC..0x080C6480: 436 bytes, 199 instructions. */
void func_080C62CC(State080C62CC *state, const u32 *items, s32 count, u8 mode)
{
    s32 i;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->count = count;
    for (i = 0; i < count; ++i)
        state->items[i] = items[i];

    state->current = 15;
    if (mode) {
        state->mode = 0;
        push_state(state);
        state->current = 11;
        push_state(state);
        state->current = 9;
        push_state(state);
        state->current = 8;
        push_state(state);
        state->current = 5;
    } else {
        state->mode = 1;
        push_state(state);
        state->current = 11;
        push_state(state);
        state->current = 9;
        push_state(state);
        state->current = 12;
    }
    push_state(state);
    state->current = 7;
    push_state(state);
    state->current = 14;

    data_0836D4BC(data_03003A60, func_080CBA3C(0), 0x20);
    request_animation(1);

    state->saved_control = g_control_flags_03000940.control;
    state->saved_attributes = g_control_flags_03000940.attributes;
    g_control_flags_03000940.control |= 0x1000;
    g_control_flags_03000940.attributes &= 0xEF;
}
