#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 input;
} Actor;

typedef struct {
    u8 unknown_0000[0x3C24];
    u32 flags;
} GlobalState;

extern Actor g_state_02000080;
extern GlobalState g_state_02000000;
extern u8 func_080C9540(u16 bitIndex);
extern u8 func_080CED5C(u8 index);
extern u8 func_080C8280(Actor *actor);
extern u8 func_080C8364(Actor *actor);
extern u8 func_080CD92C(Actor *actor);
extern u8 func_080C8348(Actor *actor);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_08009AFC(u16 event);
extern Actor *func_080C83CC(u8 category);

/* Complete [0x08009CE0, 0x08009DD0): 240 bytes, 93 instructions. */
u8 func_08009CE0(void)
{
    Actor *actor;
    GlobalState *state;

    if (func_080C9540(0x40) || !func_080CED5C(0))
        return 0;

    actor = &g_state_02000080;
    if ((actor->input & 0x81) &&
        (func_080C8280(actor) || func_080C8364(actor))) {
        if (func_080C8280(actor) && !func_080CD92C(actor) &&
            !func_080C8364(actor) && !func_080C8348(actor))
            func_080C9574(0x256, 1);
        func_08009AFC(0xAA);
        state = &g_state_02000000;
        state->flags |= 4;
        return 1;
    }

    actor = func_080C83CC(8);
    if (actor && (actor->input & 0x81) && func_080C8280(actor) &&
        !func_080CD92C(actor) && !func_080C8364(actor))
        func_080C9574(0x257, 1);
    return 0;
}
