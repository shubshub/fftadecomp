#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
} FlagState;

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
} ListState;

typedef struct {
    u32 unknown_00;
    ListState *list;
} MenuState;

extern u8 func_080543CC(ListState *list, u32 index);

/* Complete target: [0x080541B0, 0x08054202), 82 bytes. */
void func_080541B0(FlagState *state, MenuState *menu)
{
    if (func_080543CC(menu->list, 0) != 0)
        state->flags |= 4;
    else
        state->flags &= ~4;

    if (func_080543CC(menu->list, 0) == menu->list->count - 4)
        state->flags &= ~8;
    else
        state->flags |= 8;
}
