#include "control_flags.h"

// Complete [0x080EF638, 0x080EF96E): 822 bytes.
typedef struct {
    s16 value;
    u8 unknown_02[10];
} Interpolation;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *payload;
} Message;

typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u8 unknown_06[2];
    Interpolation interpolation;
    void *payload;
    void *object;
    void *unknown_1C;
    void *fade;
    u16 *overlay;
    void *transfer;
} State;

extern u8 data_0600EE40[];
extern u8 data_06005800[];
extern u8 data_06008000[];
extern const u8 data_0894D810[];

extern void *func_080DD4C4(void *);
extern void *func_080DC1E8(void *object, u8 first, u8 second, u8 mode,
                          void *source, void *destination, void *parent);
extern void *func_080DBA5C(void *);
extern u32 func_08003A74(u32);
extern u32 func_08003A80(u32);
extern void func_080034B8(u16, u8);
extern u32 func_080035A8(u8);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080DC224(void *object, s16 width, s16 height, s16 *x, s16 *y);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern void func_080E0608(Interpolation *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(Interpolation *state);
extern u8 func_080E0690(Interpolation *state);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D3F08(void *);
extern u8 func_080DD580(void *);
extern void *func_080D9914(u16, u16, void *);
extern u16 func_080D499C(u16, u16);
extern u16 *func_080D996C(void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D9B64(void *);

u32 func_080EF638(void *context, Message *message, State *state)
{
    switch (message->phase) {
    case 0:
        state->payload = message->payload;
        state->object = func_080DD4C4(state->payload);
        state->timer = 36;
        break;
    case 1:
        break;
    case 0x100:
        if (--state->timer == 0) {
            state->transfer = func_080DC1E8(state->object, 0, 0, 7,
                data_0600EE40, data_06005800, context);
            state->timer = 66;
            message->phase++;
        }
        break;
    case 0x101:
        if (state->timer != 0)
            state->timer--;
        state->transfer = func_080DBA5C(state->transfer);
        if (state->transfer == 0 && state->timer == 0) {
            s16 a, b;

            func_080034B8(func_08003A74((u32)data_06005800)
                | func_08003A80((u32)data_06008000), 2);
            {
                u32 mask = func_080035A8(2);
                u32 display = g_control_flags_03000940.display;

                display |= mask;
                g_control_flags_03000940.display = display;
            }
            func_080DBDC8(state->object, &state->x, &state->y);
            func_080DC224(state->object, state->x, state->y, &a, &b);
            func_08003508(a, 2);
            func_08003558(b, 2);
            func_080E0608(&state->interpolation, state->y, (s16)(state->y - 24), 72);
            state->fade = func_080D3E9C(data_0894D810, context);
            message->phase++;
        }
        break;
    case 0x102: {
        s16 c;

        func_080E064C(&state->interpolation);
        func_080DC224(state->object, state->x, state->interpolation.value, 0, &c);
        func_08003558(c, 2);
        if (func_080E0690(&state->interpolation)) {
            state->timer = 8;
            message->phase++;
        }
        break;
    }
    case 0x103:
        if (--state->timer == 0) {
            if (func_080DD580(state->payload)) {
                void *task;
                u16 *entries;
                u16 fill;
                u16 i;

                task = func_080D9914(2, 0, context);
                fill = func_080D499C(2, 0);
                entries = func_080D996C(task);
                for (i = 0; i < 0xA0; i++)
                    entries[i] = fill;
                func_080D9BA8(task, 1);
                state->overlay = task;
                func_080E0608(&state->interpolation, 0, 80, 36);
                state->timer = 18;
                message->phase = 0x104;
            } else {
                func_080E0608(&state->interpolation, state->y - 24, state->y - 8, 36);
                message->phase = 0x105;
            }
        }
        break;
    case 0x104: {
        s16 before = state->interpolation.value;
        u16 i;

        func_080E064C(&state->interpolation);
        if (before != state->interpolation.value) {
            u16 *entries = func_080D996C(state->overlay);
            u16 base = state->y - 72;

            for (i = 0; i < 0x38; i++) {
                if (i & 1)
                    entries[i + base]++;
                else
                    entries[i + base]--;
                if (i >= state->timer >> 1)
                    break;
            }
            state->timer += 2;
        }
        if (func_080E0690(&state->interpolation)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            message->phase++;
        }
        break;
    }
    case 0x105: {
        s16 d;

        func_080E064C(&state->interpolation);
        func_080DC224(state->object, state->x, state->interpolation.value, 0, &d);
        func_08003558(d, 2);
        if (func_080E0690(&state->interpolation)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            message->phase++;
        }
        break;
    }
    case 0x106:
        state->fade = func_080D3F08(state->fade);
        if (state->fade == 0) {
            state->overlay = func_080D9B64(state->overlay);
            if (state->overlay == 0)
                message->phase = 2;
        }
        break;
    }
    return 0;
}
