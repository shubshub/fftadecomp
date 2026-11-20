#include "ffta.h"
#include "control_flags.h"
#include "history_unit.h"

/* Complete target: [0x080C6480, 0x080C6858), 984 bytes, including the
   jump table and literal pools. */

typedef struct State080C62CC {
    HistoryUnit *items[12];
    HistoryUnit *received[12];
    u8 mode;
    u8 unit;
    u8 count;
    u8 block;
    s8 delay;
    u8 unknown_65;
    u16 saved_control;
    u16 saved_attributes;
    u16 unknown_6A;
    u16 current;
    u16 depth;
    u16 history[34];
} State080C62CC;

typedef struct {
    u8 flags;
    u8 unknown_01;
    u8 mode;
    u8 unknown_03[0x121];
    union {
        u16 packed;
        struct {
            u8 phase;
            u8 flags;
        } bytes;
    } status;
} System080C6480;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 current;
    u8 pending;
    u16 x;
    u16 y;
    u8 unknown_08[0x40];
    u16 active;
    u8 unknown_4A[0x46];
} Animation080C6480;

extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern System080C6480 data_030028A0;
extern u32 data_02015830[];
extern Animation080C6480 data_02015744;
extern const char data_08149A1C[];
extern const char data_08149A28[];
extern const char data_08149A30[];
extern const char data_08149A38[];
extern void func_08005028(void);
extern s32 func_08003B1C(const char *first, const char *second);
extern u32 func_08003D20(const void *source, void *destination, u16 length);
extern u32 func_08003D9C(const void *send, void *send_destination,
                         u16 send_count, void *receive, void *receive_source,
                         u16 receive_count);
extern u8 func_080C95A8(u16 index);

/* An inlined copy of func_080C71B4 (src/080C71B4.c). */
static inline void request_animation(u16 request)
{
    u8 value;
    Animation080C6480 *animation;

    if (!func_080C95A8(13))
        return;
    value = request;
    animation = &data_02015744;
    if (animation->current) {
        if (animation->current == value)
            return;
        animation->flags |= 4;
        animation->pending = value;
    } else {
        g_callbacks_0836D4B8[0](animation, sizeof(*animation));
        animation->current = value;
        animation->x = 216;
        animation->y = 152;
        if (value)
            animation->active = 1;
    }
}

u8 func_080C6480(State080C62CC *state)
{
    switch (state->current) {
    case 0:
        func_08005028();
        state->current = state->history[--state->depth];
        break;
    case 1:
        if (func_08003B1C(data_08149A1C, data_08149A28))
            state->current = 2;
        break;
    case 4:
        if (func_08003B1C(data_08149A30, data_08149A38))
            state->current = 2;
        break;
    case 2:
        if (data_030028A0.status.packed == 0x101 && data_030028A0.mode == 3) {
            state->delay = 0;
            state->current = 3;
        }
        break;
    case 3:
        if (state->delay <= 7) {
            state->delay++;
            break;
        }
        state->current = state->history[--state->depth];
        break;
    case 7: {
        /* 0x080C656A reads state->mode before 0x080C656C loads the
           callback table; 0x080C657C reads it again after the call. */
        u8 mode = state->mode;
        u32 *list;
        s32 i;

        g_callbacks_0836D4B8[0](&data_02015830[mode * 16], 2);
        list = &data_02015830[state->mode * 16];
        for (i = 0; i < state->count; i++)
            list[i + 1] = (u32)state->items[i];
        list[0] = state->count;
        state->current = state->history[--state->depth];
        break;
    }
    case 5:
        state->delay = 4;
        state->current = 6;
        break;
    case 6:
        if (state->delay > 0) {
            state->delay--;
            break;
        }
        state->current = state->history[--state->depth];
        break;
    case 8: {
        u32 *local = &data_02015830[state->mode * 16];
        u32 *remote = &data_02015830[(state->mode ^ 1) * 16];

        if (func_08003D9C(local, local, (state->count + 2) * 2, remote, remote,
                          (state->count + 2) * 2))
            state->current = 14;
        break;
    }
    case 9: {
        u32 *other = &data_02015830[(state->mode ^ 1) * 16];
        s32 i;

        for (i = 0; i < other[0]; i++)
            state->received[i] = (HistoryUnit *)other[i + 1];
        if (state->mode)
            state->count = other[0];
        state->current = state->history[--state->depth];
        break;
    }
    case 11:
        if (state->unit + 1 > state->count) {
            state->current = state->history[--state->depth];
            break;
        }
        state->block = 0;
        /* 0x080C66AC-0x080C66B0 loads state->mode and discards it: the
           mode test is in the ROM, its two arms are the same push. */
        if (state->mode) {
            state->history[state->depth++] = state->current;
            state->current = 10;
        } else {
            state->history[state->depth++] = state->current;
            state->current = 10;
        }
        break;
    case 10: {
        s32 offset = state->block * 64;
        s32 n = sizeof(HistoryUnit) - offset;

        if (n <= 0) {
            state->unit++;
            state->current = state->history[--state->depth];
            break;
        }
        if (n > 64)
            n = 64;
        if (state->mode) {
            state->block++;
            state->history[state->depth++] = state->current;
            state->current = 13;
            break;
        }
        if (!func_08003D20((u8 *)state->items[state->unit] + offset,
                           (u8 *)state->received[state->unit] + offset, n >> 1))
            break;
        state->block++;
        state->history[state->depth++] = state->current;
        state->current = 14;
        break;
    }
    case 12:
        if (data_030028A0.status.bytes.flags == 12)
            state->current = 14;
        break;
    case 13:
        if (data_030028A0.status.bytes.flags == 5)
            state->current = 14;
        break;
    case 14:
        if (data_030028A0.status.packed == 0x101 && data_030028A0.mode == 3)
            state->current = 5;
        break;
    case 15:
        g_control_flags_03000940.display = state->saved_control;
        g_control_flags_03000940.bldcnt_lo = state->saved_attributes;
        request_animation(0);
        return 0;
    }
    return 1;
}
