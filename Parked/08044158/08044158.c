#include "ffta.h"

typedef struct {
    u8 category : 3;
    u8 unknown_03 : 5;
    u8 unknown_08 : 7;
    u8 disabled : 1;
    u8 selection : 5;
    u8 primary : 1;
    u8 secondary : 1;
    u8 unknown_17 : 1;
    u8 unknown_03_byte;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

typedef struct {
    u8 unknown_00[0x224];
    ActionEntry entries[5];
} ActionCollection;

typedef struct {
    u8 unknown_00 : 1;
    u8 active : 1;
    u8 layer : 3;
    u8 unknown_05 : 3;
    u8 unknown_01[5];
    u16 x;
    u16 y;
    u8 unknown_0A[0x5C];
    u8 cursor;
    u8 reason;
    u8 unknown_68[0x26];
    u8 state : 3;
    u8 unknown_473 : 5;
} ActionPanel;

typedef struct {
    ActionCollection *actions;
    ActionPanel *panel;
    u8 unknown_08[0x7AC];
    u8 selection;
} MenuState;

extern MenuState *g_state_03002810;
u32 func_080445BC(ActionEntry *entry, u32 mode);
u32 func_08035A20(u8 selection);
u32 func_08035A44(u8 selection);
void func_08035844(u32 mode);

/* Complete target: [0x08044158, 0x080443EE), 662 bytes. */
u32 func_08044158(u32 mode)
{
    s32 i;

    for (i = 0; i <= 4; i++) {
        ActionEntry *entries = g_state_03002810->actions->entries;
        if (mode == 0) {
            ActionEntry *entry = entries + i;
            if (entry->disabled) {
                continue;
            }
            if (entry->primary && entry->category && func_080445BC(entry, 1)) {
                g_state_03002810->panel->active = 1;
                g_state_03002810->panel->layer = 0;
                g_state_03002810->panel->x = func_08035A20(entry->selection - 1) + 6;
                g_state_03002810->panel->y = func_08035A44(entry->selection - 1) + 4;
                g_state_03002810->panel->state = 3;
                g_state_03002810->panel->reason = 1;
                g_state_03002810->panel->cursor = i + 1;
                g_state_03002810->selection = 0;
                func_08035844(0);
                return 1;
            }
        } else {
            ActionEntry *entry = entries + i;
            if (entry->id != 0) {
                if (entry->disabled) {
                    continue;
                }
                if (entry->primary && entry->category && func_080445BC(entry, 1)) {
                g_state_03002810->panel->active = 1;
                g_state_03002810->panel->layer = 0;
                g_state_03002810->panel->x = func_08035A20(entry->selection - 1) + 6;
                g_state_03002810->panel->y = func_08035A44(entry->selection - 1) + 4;
                g_state_03002810->panel->state = 3;
                g_state_03002810->panel->reason = 1;
                g_state_03002810->panel->cursor = i + 1;
                g_state_03002810->selection = 0;
                func_08035844(0);
                return 1;
                }
            }
        }
        {
            ActionEntry *entry = entries + i;
            if (!entry->disabled && entry->secondary && entry->category && entry->selection) {
                g_state_03002810->panel->active = 1;
                g_state_03002810->panel->layer = 0;
                g_state_03002810->panel->x = func_08035A20(entry->selection - 1) + 6;
                g_state_03002810->panel->y = func_08035A44(entry->selection - 1) + 4;
                g_state_03002810->panel->state = 3;
                g_state_03002810->panel->reason = 2;
                g_state_03002810->panel->cursor = i + 1;
                g_state_03002810->selection = 0;
                func_08035844(0);
                return 2;
            }
        }
    }
    return 0;
}
