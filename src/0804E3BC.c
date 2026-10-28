#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *unit;
    u16 width;
    u16 height;
    u8 unknown_0C[4];
    u8 flags;
} MenuState0804E3BC;

void *func_08005BFC(void *task);
void func_08017E28(MenuState0804E3BC *state);

void func_0804E3BC(void *task, u8 enabled)
{
    MenuState0804E3BC *state =
        (MenuState0804E3BC *)((u8 *)func_08005BFC(task) + 0x7C);

    if (enabled) {
        if (state != 0) {
            state->flags &= 0xBF;
            func_08017E28(state);
        }
    } else {
        if (state != 0) {
            if (state->width <= 224 && state->height <= 64)
                state->flags &= 0xFB;
            state->flags |= 0x40;
        }
    }
}
