#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 priority;
} Descriptor0810CC44;

typedef struct {
    u16 index;
    u8 count;
    u8 timer;
    u8 priority;
    u8 flag;
    u8 unknown_06[6];
    void *handles[2];
    u8 unknown_14[8];
    void *loading;
    void *actor;
} State0810CC44;

typedef struct {
    u32 unknown_00;
    void *resource;
    u32 unknown_08[3];
    u16 index;
    u16 effect;
    u16 variant;
    u16 unknown_1a;
} Params0810CC44;

typedef void (*Initializer0810CC44)(void *, u32);
extern Initializer0810CC44 const g_callbacks_0836D4B8[];
extern const u8 data_083A2638[];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080E051C(void *);
extern u32 func_080E0570(void **, u16);
extern void *func_080DD4A4(void *, u8);
extern int func_080E2398(void *, void *, void *);
extern int func_0810CB68(void *, void *, void *);
extern void *func_08005B6C(int (*)(void *, void *, void *), u16, void *, void *);

int func_0810CC44(void *owner, Descriptor0810CC44 *descriptor, State0810CC44 *state)
{
    Params0810CC44 first, params;
    u8 position;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        state->priority = descriptor->priority;
        state->actor = descriptor->actor;
        if (descriptor->flags & 2)
            state->flag = 1;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (state->flag) {
            g_callbacks_0836D4B8[0](&first, sizeof(first));
            /* The original loads the base effect and adds the variant offset. */
            first.effect = 0x159;
            first.effect += 0xB2;
            first.variant = 0x51;
            first.resource = state->actor;
            state->handles[0] = func_08005B6C(func_080E2398, 0x28, &first, owner);
        }
        descriptor->phase++;
        break;
    case 0x101:
        state->handles[0] = func_080E051C(state->handles[0]);
        if (state->handles[0])
            break;
        animation = 2;
        if (state->priority)
            animation = 0;
        state->loading = func_080E03F8(state->actor, data_083A2638, animation, 1, 0, owner);
        descriptor->phase++;
        break;
    case 0x102:
        state->loading = func_080E05DC(state->loading);
        if (state->loading)
            break;
        state->count = func_080D8858(state->actor, 0);
        if (!state->count) {
            descriptor->phase = 2;
            break;
        }
        state->timer = 1;
        descriptor->phase++;
        break;
    case 0x103:
        func_080E0570(state->handles, 2);
        state->timer--;
        if (state->timer)
            break;
        position = state->handles[0] != 0;
        params.index = state->index;
        params.resource = func_080DD4A4(state->actor, state->index);
        state->handles[position] = func_08005B6C(func_0810CB68, 0x20, &params, owner);
        state->timer = 0x28;
        state->index++;
        if (state->index == state->count)
            descriptor->phase++;
        break;
    case 0x104:
        if ((u8)func_080E0570(state->handles, 2))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
