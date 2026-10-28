#include "ffta.h"

struct EntrySpecification {
    u8 slot : 3;
    u8 unknown_03 : 5;
    u8 unknown_01;
    u8 selection : 5;
    u8 blocked : 2;
    u8 unknown_17 : 1;
    u8 unknown_03_bytes[3];
} __attribute__((packed));

struct Source {
    u8 unknown_000[0x224];
    struct EntrySpecification entries[5];
};

struct MenuEntry {
    u16 active : 1;
    u16 unknown_01 : 15;
    u8 unknown_02;
    u8 slot;
    u8 unknown_04[0x30];
};

struct MenuContext {
    struct Source *source;
    u8 unknown_004[0x7B4];
    struct MenuEntry entries[6];
};

struct SelectionState {
    u8 unknown_0000[0x1F69];
    u8 selected;
    u8 unknown_1F6A[0xEEA];
    u8 selection : 5;
    u8 unknown_05 : 3;
};

extern struct MenuContext *g_state_03002810;
extern struct SelectionState g_state_02000000;

/* Complete target: [0x0804409C, 0x0804413C), 160 bytes. */
void func_0804409C(void)
{
    struct Source *source = g_state_03002810->source;
    struct EntrySpecification *entry;
    int index;

    g_state_02000000.selected = g_state_03002810->entries[0].slot + 1;
    g_state_02000000.selection = g_state_03002810->entries[0].slot + 1;
    entry = source->entries;
    for (index = 0; index < 5; index++) {
        u8 slot = entry->slot;

        if (slot != 0 && !entry->blocked &&
            g_state_03002810->entries[slot].active)
            entry->selection = g_state_03002810->entries[slot].slot + 1;
        entry++;
    }
}
