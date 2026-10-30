#include "ffta.h"

typedef struct {
    u32 value;
    void *task;
    u16 current;
    u16 count;
    u16 history[34];
} State080BC40C;

extern void func_080D376C(void);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern void *func_080D3508(u16 action, void *resource, u32 value);
extern u8 func_080D3878(const void *task);
extern void func_080D3864(void *task);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);

/* Complete [0x080BC40C, 0x080BC4BA), 174 bytes:
 * 10b5041c208906284dd88000014940180068874624c40b0840c40b084ac40b08
 * 5ac40b0870c40b0884c40b088ec40b08aec40b0817f094f90120208133e017f0
 * d5f9000600282ed017f0acfa1be004482268002117f052f860600320208122e0
 * 69010000606817f001fa000600281ad0606817f0f1f909e017f092f905202081
 * 11e017f099f9000600280cd06089013860810004c00b211c0c31091808882081
 * 01e0002000e0012010bc02bc0847
 */
u32 func_080BC40C(State080BC40C *state)
{
    switch (state->current) {
    case 0:
        func_080D376C();
        state->current = 1;
        break;
    case 1:
        if (!func_080D37F8())
            break;
        if (!func_080D39B0())
            break;
        goto advance;
    case 2:
        state->task = func_080D3508(0x169, 0, state->value);
        state->current = 3;
        break;
    case 3:
        if (!func_080D3878(state->task))
            break;
        func_080D3864(state->task);
        goto advance;
    case 4:
        func_080D37AC();
        state->current = 5;
        break;
    case 5:
        if (!func_080D37C4())
            break;
    advance:
        state->current = state->history[--state->count];
        break;
    case 6:
        return 0;
    }
    return 1;
}
