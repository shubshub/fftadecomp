#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
} Actor;

typedef struct {
    u8 unknown_0000[0x2190];
    u8 phase;
    u8 unknown_2191[0x2FC4 - 0x2191];
    Actor selected;
    u8 unknown_after_selected[0x3C24 - 0x2FC4 - sizeof(Actor)];
    u32 flags;
    u8 unknown_3C28[2];
    u8 mode;
} GlobalState;

extern GlobalState g_state_02000000;
extern u8 func_080C9540(u32 mask);
extern Actor *func_08125578(u32 index);
extern u8 func_080C8348(Actor *actor);
extern u8 func_080C8364(Actor *actor);
extern void func_08009AFC(u32 sound);
extern u8 func_080C8280(Actor *actor);
extern u8 func_080CD8CC(Actor *actor);
extern u8 func_080CD92C(Actor *actor);

u8 func_08009DD0(void)
{
    GlobalState *state;
    Actor *actor;

    if (func_080C9540(0x40))
        return 0;
    state = &g_state_02000000;
    if (state->phase == 8) {
        actor = func_08125578(10);
        if (func_080C8348(actor) || func_080C8364(actor)) {
            func_08009AFC(0xAA);
            state->flags |= 4;
            return 1;
        }
    } else if (state->mode == 0x31 || state->mode == 0x39) {
        actor = &state->selected;
        if (!actor->active ||
            (func_080C8280(actor) && !func_080CD8CC(actor)) ||
            func_080CD92C(actor) || func_080C8364(actor) ||
            func_080C8348(actor)) {
            func_08009AFC(0xAA);
            return 1;
        }
    }
    return 0;
}
