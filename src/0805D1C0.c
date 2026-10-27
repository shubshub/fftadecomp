#include "ffta.h"

/* 0x0805D1C0..0x0805D23C: 124 bytes. */
typedef struct {
    u8 unknown_00;
    u8 flags;
    u16 count;
} MenuEntry;

typedef struct {
    u8 unknown_00[0x11AA];
    u8 selected;
    u8 unknown_11AB[0x9D];
    MenuEntry *entries[0];
} MenuState;

extern MenuState *data_0200F448;
extern u32 func_080C9540(u32);

u32 func_0805D1C0(u8 option)
{
    int i = 0;
    MenuState *state = data_0200F448;

    for (; i < 2; i++) {
        MenuEntry *entry = state->entries[state->selected + i];

        if (entry && entry->count && (entry->flags & 1))
            return 0x54;
    }
    if (!(u8)func_080C9540(0x202) && option)
        return 0x58;
    if (!(u8)func_080C9540(0x202))
        return 0x59;
    return 0x4D;
}
