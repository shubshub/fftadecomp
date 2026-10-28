#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 flags : 6;
} ItemEntry;

typedef struct {
    u8 unknown_00[0x424];
    ItemEntry *entries[0];
} MenuState;

typedef struct {
    MenuState *state;
} MenuContext;

extern u32 func_080CE4DC(u16 id, u32 field);
extern u32 func_080CB9CC(u32 category);

/* Complete target: [0x080674B0, 0x08067504), 84 bytes, 37 instructions. */
u8 func_080674B0(MenuContext *context, s32 index)
{
    ItemEntry *entry = context->state->entries[index];
    u8 category = func_080CE4DC(entry->id, 2);

    category += 15;
    if (func_080CE4DC(entry->id, 1) == 1)
        category = 6;
    return func_080CB9CC(category);
}
