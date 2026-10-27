#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 flags;
    u16 progress;
    u8 type;
} MenuState0804E1F0;

extern MenuState0804E1F0 *func_08005BFC(void *task);
extern void func_08050E34(MenuState0804E1F0 *state);
extern void func_08050E54(MenuState0804E1F0 *state);

/* Complete [0x0804E1F0, 0x0804E222): 50 bytes, 22 instructions. */
void func_0804E1F0(void *task)
{
    MenuState0804E1F0 *state = func_08005BFC(task);

    state->progress = 0;
    state->flags |= 0x20;
    if (state->type <= 8)
        func_08050E34(state);
    if (state->type == 1)
        func_08050E54(state);
}
