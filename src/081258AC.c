#include "ffta.h"

/* 0x081258AC..0x081258CC: 32 bytes. */
typedef struct {
    u8 unknown_00;
    u8 active;
    u8 unknown_02[0x92];
    u16 flags;
} SelectionState;

extern SelectionState g_state_0200F390;
extern void func_08124850(u8);

void func_081258AC(void)
{
    SelectionState *state = &g_state_0200F390;

    state->active = 1;
    state->flags |= 1;
    func_08124850(0xFF);
}
