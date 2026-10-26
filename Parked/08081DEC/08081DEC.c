#include "ffta.h"

/* Complete [0x08081DEC, 0x08081FB0): 452 bytes, 191 instructions. */
typedef struct {
    u16 id;
    u16 flags;
    u8 unknown_04[8];
    u16 value;
    u8 unknown_0e[6];
} MenuEntry;

typedef struct {
    u8 unknown_00[0x18];
    MenuEntry *entries;
} EntryTable;

typedef struct {
    u8 unknown_00[0x20];
} ScrollView;

typedef struct {
    u8 unknown_00[0x11];
    s8 current;
    u8 unknown_12[0x1e];
} Selector;

typedef struct {
    u8 unknown_00[0x38];
    u16 value;
    u8 unknown_3a[4];
    u16 action;
    u16 selected_id;
    u8 unknown_42[6];
    EntryTable *primary;
    u8 unknown_4c[0x2c];
    ScrollView view;
    Selector selector;
    EntryTable *secondary;
} MenuPanel;

typedef struct {
    u8 unknown_0000[0x2c88];
    MenuPanel panels[1];
} MenuState;

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeated;
} InputState;

extern InputState data_03000000;
extern MenuState *data_03002818;
extern u16 func_08017B68(ScrollView *, u32);
extern u16 func_08017B50(ScrollView *);
extern u8 func_08017A90(ScrollView *, u16);
extern void func_08141540(s32);
extern void func_08081D28(u32, u16, s8, u8);

s32 func_08081DEC(u32 panel)
{
    if (data_03000000.pressed == 4) {
        ScrollView *view = &data_03002818->panels[panel].view;
        Selector *selector = (Selector *)((u8 *)data_03002818 + sizeof(MenuPanel) * panel + 0x2d20);
        s8 selected = func_08017B68(view, selector->current);
        u16 *value = &data_03002818->panels[panel].value;
        MenuEntry *entry = data_03002818->panels[panel].primary->entries;
        entry = selected + entry;
        *value = entry->value;
        if (entry->value)
            return 10;
        func_08141540(0x6a);
    }
    if (data_03000000.pressed == 1) {
        EntryTable *table = data_03002818->panels[panel].secondary;
        Selector *selector = (Selector *)((u8 *)data_03002818 + sizeof(MenuPanel) * panel + 0x2d20);
        u16 selected = func_08017B68(&data_03002818->panels[panel].view,
                                    selector->current);
        MenuEntry *entry = table->entries;
        entry = selected + entry;
        if (!(entry->flags & 1)) {
            data_03002818->panels[panel].selected_id = entry->id;
            data_03002818->panels[panel].action = 1;
        }
    }
    if (data_03000000.pressed == 2)
        data_03002818->panels[panel].action = 2;

    if (data_03000000.repeated == 0x80) {
        MenuState *state = data_03002818;
        Selector *selector = (Selector *)((u8 *)state + sizeof(MenuPanel) * panel + 0x2d20);
        s8 next = selector->current + 1;
        if (next < func_08017B50(&data_03002818->panels[panel].view)) {
            func_08081D28(panel, 0x80, next, 0);
        } else if (func_08017A90(&data_03002818->panels[panel].view, 0x80)) {
            func_08081D28(panel, 0x80, next, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        MenuState *state = data_03002818;
        Selector *selector = (Selector *)((u8 *)state + sizeof(MenuPanel) * panel + 0x2d20);
        s8 next = selector->current - 1;
        if (next < 0) {
            if (func_08017A90(&data_03002818->panels[panel].view, 0x40)) {
                func_08081D28(panel, 0x40, next, 1);
                return 7;
            }
        } else {
            func_08081D28(panel, 0x40, next, 0);
        }
    }
    return 6;
}
