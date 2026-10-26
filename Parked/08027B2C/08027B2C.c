#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 y;
    u8 unknown_02;
    u8 visible_count;
    u16 count;
    u8 unknown_06[0xE];
} MenuLayout;

typedef struct {
    u8 unknown_00[0x80];
    MenuLayout layout;
    u32 *entries;
    u8 *enabled;
} MenuPanel;

typedef struct {
    u8 unknown_00[0x480];
    u8 option_codes[7];
} MenuContext;

typedef struct {
    u8 unknown_00[0x2190];
    u8 mode;
    u8 unknown_2191[0x1A99];
    u8 selection;
} GameState;

typedef struct {
    u8 unknown_00[7];
    u8 restricted;
    u8 unknown_08[4];
} SelectionRecord;

extern MenuContext *data_0200F438;
extern GameState g_state_02000000;
extern const SelectionRecord g_table_08563A70[];

u32 func_080C9540(u32 flag);
u32 func_080C95A8(u32 flag);
u32 func_08027AE8(void);
void func_08096D7C(void);
u32 func_08099544(void);

/* Complete target: [0x08027B2C, 0x08027D10), 484 bytes. */
void func_08027B2C(MenuPanel *panel)
{
    MenuLayout *layout = &panel->layout;
    s32 index;

    panel->entries[0] = 1;
    data_0200F438->option_codes[0] = 1;
    index = 1;
    if ((u8)func_080C9540(2) != 0) {
        layout->count--;
    } else {
        panel->entries[1] = 2;
        data_0200F438->option_codes[1] = 2;
        index = 2;
    }

    if ((u8)func_080C9540(2) != 0) {
        layout->count--;
    } else {
        if ((u8)func_080C9540(0x207) != 0) {
            panel->entries[index] = 3;
        } else {
            panel->entries[index] = 7;
        }
        if ((u8)func_08027AE8() == 0) {
            panel->enabled[index] = 0;
        }
        data_0200F438->option_codes[index] = 3;
        index++;
    }

    panel->entries[index] = 4;
    data_0200F438->option_codes[index] = 4;
    index++;

    if ((u8)func_080C9540(2) != 0) {
        layout->count--;
    } else {
        const SelectionRecord *record = &g_table_08563A70[g_state_02000000.selection];
        panel->entries[index] = 5;
        func_08096D7C();
        if (func_08099544() == 0 || g_state_02000000.mode == 2 || record->restricted != 0) {
            panel->enabled[index] = 0;
        }
        data_0200F438->option_codes[index] = 5;
        index++;
    }

    if ((u8)func_080C9540(2) != 0) {
        layout->count--;
    } else {
        panel->entries[index] = 6;
        data_0200F438->option_codes[index] = 6;
        if ((u8)func_080C95A8(13) == 1) {
            panel->enabled[index] = 0;
        }
    }

    layout->visible_count = layout->count;
    if (layout->count <= 5) {
        layout->y += (6 - layout->count) * 2;
    }
}
