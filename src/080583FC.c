#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
} FlagState;

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    u8 position;
} ListState;

typedef struct {
    u32 unknown_00;
    ListState *list;
} MenuState;

/* Complete target: [0x080583FC, 0x0805843C), 64 bytes. */
void func_080583FC(FlagState *state, MenuState *menu)
{
    if (menu->list->position != 0)
        state->flags |= 4;
    else
        state->flags &= ~4;

    if (menu->list->position == menu->list->count - 3)
        state->flags &= ~8;
    else
        state->flags |= 8;
}
