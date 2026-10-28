#include "ffta.h"

typedef struct {
    u8 identifier;
    u8 flags;
    u16 count;
} MenuEntry;

typedef struct {
    u8 unknown_00[4];
    u8 active[0];
} SlotFlags;

typedef struct {
    u8 unknown_0000[0x11AA];
    u8 selected;
    u8 unknown_11AB[0x9D];
    MenuEntry *entries[130];
    SlotFlags *slot_flags;
} MenuState;

extern MenuState *data_0200F448;

/* Complete [0x0805DDC8, 0x0805DE30): 104 bytes, 44 reachable Thumb instructions. */
void func_0805DDC8(u16 index)
{
    MenuEntry *entry = data_0200F448->entries[data_0200F448->selected + index];

    if (entry != 0) {
        entry->count = 0;
        entry->flags &= ~1;
        data_0200F448->entries[data_0200F448->selected + index] = 0;
    }
    data_0200F448->slot_flags->active[index] = 0;
}
