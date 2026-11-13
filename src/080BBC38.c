#include "ffta.h"

// Complete [0x080BBC38, 0x080BBD32): 250 bytes, 91 instructions.
// Runs the step queue built by func_080BBBB0.

typedef struct Context080BBC38 {
    u8 unknown_00[0x1F];
    s8 direction;
} Context080BBC38;

typedef struct State080BBC38 {
    Context080BBC38 *context;
    void *handle;
    u16 parameter;
    u8 unknown_0A[2];
    u16 current;
    u16 count;
    u16 steps[5];
} State080BBC38;

extern u8 func_080BD130(u8 value);
extern void func_080D376C(void);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern void *func_080D3508(u16 resource, u32 mode, void *context);
extern u8 func_080D3878(void *handle);
extern void func_080D3864(void *handle);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);

static inline void next_step(State080BBC38 *state)
{
    state->current = state->steps[--state->count];
}

u32 func_080BBC38(State080BBC38 *state)
{
    switch (state->current) {
    case 0:
        if (!func_080BD130(0)) {
            func_080D376C();
            state->current = 1;
        }
        break;
    case 1:
        if (func_080D37F8() && func_080D39B0())
            next_step(state);
        break;
    case 3:
        state->handle = func_080D3508(0x156, 0, (void *)1);
        state->current = 5;
        break;
    case 4:
        if (!func_080BD130(1)) {
            state->handle = func_080D3508(0x157, 0, (void *)1);
            state->current = 5;
        }
        break;
    case 2:
        state->handle = func_080D3508(state->parameter, 0, state->context);
        state->current = 5;
        break;
    case 5:
        if (func_080D3878(state->handle)) {
            func_080D3864(state->handle);
            state->handle = 0;
            next_step(state);
        }
        break;
    case 6:
        func_080D37AC();
        state->current = 7;
        break;
    case 7:
        if (func_080D37C4()) {
            func_0809836C(state->context, 0, state->context->direction, 0);
            next_step(state);
        }
        break;
    case 8:
        return 0;
    }
    return 1;
}
