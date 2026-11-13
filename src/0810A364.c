// Target: complete [0x0810A364, 0x0810A4B0), 332 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 priority;
} Descriptor0810A364;

typedef struct {
    u8 count;
    u8 index;
    u8 timer;
    u8 flag;
    u8 priority;
    u8 unknown_05[3];
    void *handle;
    void *handles[2];
    void *loading;
    void *actor;
} State0810A364;

typedef struct {
    u32 unknown_00;
    void *resource;
    u32 unknown_08[3];
    u16 index;
    u16 unknown_16;
    u32 unknown_18;
} Params0810A364;

extern const u8 data_083A1A98[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080E051C(void *);
extern u8 func_080E0570(void **, u32);
extern void *func_080DD4A4(void *, u8);
extern u32 func_0810A134(void *, void *, void *);
extern u32 func_0810A2A4(void *, void *, void *);
extern void *func_08005B6C(u32 (*)(void *, void *, void *), u32,
                           Params0810A364 *, void *);

u32 func_0810A364(void *task, Descriptor0810A364 *descriptor,
                  State0810A364 *state)
{
    Params0810A364 first;
    Params0810A364 params;
    u8 position;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        state->priority = descriptor->priority;
        state->actor = descriptor->actor;
        if (descriptor->flags & 2)
            state->flag = 1;
        animation = 5;
        if (state->priority != 0)
            animation = 0;
        state->loading = func_080E03F8(state->actor, data_083A1A98,
            animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->loading = func_080E05DC(state->loading);
        if (state->loading != 0)
            break;
        state->count = func_080D8858(state->actor, 0);
        if (state->count == 0) {
            descriptor->phase = 2;
            break;
        }
        state->handle = func_08005B6C(func_0810A134, 0x4c, &first, task);
        state->timer = 0x3c;
        descriptor->phase++;
        break;
    case 0x101:
        state->handle = func_080E051C(state->handle);
        func_080E0570(state->handles, 2);
        state->timer--;
        if (state->timer != 0)
            break;
        position = state->handles[0] != 0;
        params.index = state->index;
        params.resource = func_080DD4A4(state->actor, state->index);
        state->handles[position] = func_08005B6C(func_0810A2A4, 0x28, &params, task);
        state->timer = 0x28;
        state->index++;
        if (state->index == state->count)
            descriptor->phase++;
        break;
    case 0x102:
        state->handle = func_080E051C(state->handle);
        if (state->handle != 0)
            break;
        if (func_080E0570(state->handles, 2) != 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
