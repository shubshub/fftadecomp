#include "ffta.h"
#include "control_flags.h"

// Target 0x0810C730, complete [0x0810C730, 0x0810C8D0), 416 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *source;
    u8 unknown_08[12];
    u16 flags;
} Event0810C730;

typedef struct {
    u8 flags;
    u8 countdown;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *source;
    void *position;
    u32 result;
    void *task14;
    void *task18;
    void *task1C;
    void *task20;
    void *task24;
} State0810C730;

extern const u8 data_088F46CC[], data_0894C6A8[], data_0894D69C[];
extern const u8 data_083A25E0[], data_083A25F8[], data_083A2618[];
extern u16 data_03003860[];

extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u32 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, u32 *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

s32 func_0810C730(void *context, Event0810C730 *event, State0810C730 *state)
{
    u16 options;

    switch (event->phase) {
    case 0:
        state->flags = event->flags;
        state->source = event->source;
        state->position = func_080DD748(state->source, &state->x, &state->y, 0);
        data_03003860[0x61] = 0x7FFF;
        break;
    case 1:
        break;
    case 0x100:
        func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
        g_control_flags_03000940.winout_lo = 63 & ~func_080035D0(3);
        g_control_flags_03000940.winout_hi = 63;
        g_control_flags_03000940.display |= 0x8000;
        state->task1C = func_080D4704(data_0894C6A8, context);
        state->task18 = func_080D3E9C(data_0894D69C, context);
        func_080D3F84(state->task18, 8, 255);
        state->task14 = func_080D6098(state->x, state->y, 0, 1, 1,
                                      &state->result, data_083A25E0, context);
        if (state->flags & 1)
            options = 4;
        else
            options = 2;
        state->task20 = func_080DCFE4(state->source, data_083A25F8, 12, 20,
                                      options, context, 20);
        if (state->flags & 1)
            options = 16;
        else
            options = 8;
        state->task24 = func_080DFD8C(data_083A2618, 1, options | 4, 0, context);
        state->countdown = 18;
        event->phase++;
        break;
    case 0x101:
        if (state->countdown != 0) {
            state->countdown--;
            if (state->countdown == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                g_control_flags_03000940.display &= 0x7FFF;
            }
        }
        state->task14 = func_080D6134(state->task14);
        if (state->task14 != 0)
            break;
        state->task18 = func_080D3F08(state->task18);
        if (state->task18 != 0)
            break;
        state->task1C = func_080D4774(state->task1C);
        if (state->task1C != 0)
            break;
        state->task20 = func_080DBA5C(state->task20);
        if (state->task20 == 0)
            event->phase = 2;
        break;
    }
    return 0;
}
